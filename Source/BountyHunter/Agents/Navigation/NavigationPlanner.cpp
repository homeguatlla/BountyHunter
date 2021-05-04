#include "NavigationPlanner.h"
#include <NAI/include/navigation/INavigationPlanner.h>
#include <BountyHunter/Agents/Navigation/NavigationPath.h>

#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Runtime/NavigationSystem/Public/NavigationPath.h"

#include "NavFilters/NavigationQueryFilter.h"

#include <algorithm>
#include <sstream>


#include "PropertyEditorModule.h"
#include "BountyHunter/utils/UtilsLibrary.h"

NavigationPlanner::NavigationPlanner(UWorld* world) : mWorld(world)
{
	FindLocations();
	CalculateCostMatrix();	
}

void NavigationPlanner::FindLocations()
{
	TArray<AActor*> wayPoints;
	UGameplayStatics::GetAllActorsOfClass(mWorld, ATargetPoint::StaticClass(), wayPoints);

	for (auto i = 0; i < wayPoints.Num(); ++i)
	{
		auto locationName = GetLocationNameGivenAWayPoint(wayPoints[i]);
		mLocations.push_back(Location(locationName, wayPoints[i]));
	}
}

void NavigationPlanner::GetPathFromTo(const glm::vec3& origin, const glm::vec3& destination, PathFromToCallback callback)
{
	mPathFromToCallback = callback;
	auto currentNavigationSystem = UNavigationSystemV1::GetCurrent(mWorld);

	//TODO the navAgentProperties need to be get from character not hardcoded.
	FNavAgentProperties navAgentProperties;
	navAgentProperties.AgentHeight = 100;
	navAgentProperties.AgentRadius = 10;
	navAgentProperties.bCanWalk = true;
	navAgentProperties.bCanFly = false;

	FPathFindingQuery navParams;
	navParams.EndLocation = FVector(destination.x, destination.y, destination.z);
	navParams.StartLocation = FVector(origin.x, origin.y, origin.z);
	ANavigationData* navData = currentNavigationSystem->MainNavData;
	navParams.QueryFilter = UNavigationQueryFilter::GetQueryFilter<UNavigationQueryFilter>(*navData);
	navParams.NavData = navData;

	FNavPathQueryDelegate del;
	del.BindRaw(this, &NavigationPlanner::OnPathFound);

	currentNavigationSystem->FindPathAsync(navAgentProperties, navParams, del, EPathFindingMode::Regular);
}

std::shared_ptr<NAI::Navigation::INavigationPath> NavigationPlanner::CreateNavigationPath(TArray<FNavPathPoint>& pathPoints)
{
	auto navigationPath = std::make_shared<NavigationPath>();
	for (auto point : pathPoints)
	{
		//DrawDebugSphere(mWorld, path->PathPoints[i], 10.0f, 12, FColor(255, 0, 0));
		navigationPath->AddPoint(glm::vec3(point.Location.X, point.Location.Y, point.Location.Z));
	}

	return navigationPath;
}

void NavigationPlanner::OnPathFound(uint32 aPathId, ENavigationQueryResult::Type aResultType, FNavPathSharedPtr aNavPointer)
{
	const auto navigationPath = CreateNavigationPath(aNavPointer->GetPathPoints());
	mPathFromToCallback(navigationPath);
}

bool NavigationPlanner::FillWithLocationGivenAName(const std::string& locationName, glm::vec3& location) const
{
	const auto it = std::find_if(mLocations.begin(), mLocations.end(), 
        [&locationName](const Location& location){
            return location.name == locationName;
        });

	if (it != mLocations.end())
	{
		const auto point = it->wayPoint->GetActorLocation();
		location = glm::vec3(point.X, point.Y, point.Z);
		return true;
	}
	else
	{	
		std::stringstream msg;
		msg << "Location <" << locationName << "> not found!";
		//throw std::logic_error(msg.str());
		return false;
	}
}

unsigned int NavigationPlanner::GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const
{
	auto location1 = FindLocationNearest(origin);
	auto location2 = FindLocationNearest(destination);

	unsigned int cost = 0;
	
	if (location1.name != location2.name)
	{
		const auto key = std::pair<std::string, std::string>(location1.name, location2.name);
		const auto it = mCostMatrix.find(key);
		if(it != mCostMatrix.end())
		{
			cost = it->second;
		}
		else 
		{
			cost =  std::numeric_limits<unsigned int>::max();
		}
	}
	
	cost = glm::distance(origin, destination);

	return cost;
}

bool NavigationPlanner::GetRandomReachablePointInRadius(const glm::vec3& from, float radius, glm::vec3& reachableLocation) const
{
	const auto currentNavigationSystem = UNavigationSystemV1::GetCurrent(mWorld);
	FNavLocation resultLocation;
	const bool found = currentNavigationSystem->GetRandomReachablePointInRadius(
		utils::UtilsLibrary::ConvertToFVector(from),
		radius,
		resultLocation,
		nullptr);

	if(found)
	{
		reachableLocation = utils::UtilsLibrary::ConvertToVec3(resultLocation.Location);	
	}
	
	return found;
}

std::string NavigationPlanner::GetLocationNameGivenAWayPoint(AActor* wayPoint) const
{
	const FString locationName = wayPoint->GetName();
	int32 index;
	locationName.FindChar('_', index);
	if(index > 0)
	{
		return utils::UtilsLibrary::ConvertToString(locationName.Left(index));
	}
	else
	{
		return utils::UtilsLibrary::ConvertToString(locationName);
	}
}

NavigationPlanner::Location NavigationPlanner::FindLocationNearest(const glm::vec3& point) const
{
	float minDistance = std::numeric_limits<float>::max();
	NavigationPlanner::Location nearestLocation;

	for (auto location : mLocations)
	{
		const FVector locationPoint = location.wayPoint->GetActorLocation();
		const auto distance = glm::distance(point, glm::vec3(locationPoint.X, locationPoint.Y, locationPoint.Z));
		if (distance < minDistance)
		{
			nearestLocation = location;
			minDistance = distance;
		}
	}

	return nearestLocation;
}

void NavigationPlanner::CalculateCostMatrix()
{
	auto currentNavigationSystem = UNavigationSystemV1::GetCurrent(mWorld);

	if(mLocations.empty())
	{
		return;
	}
	
	for (auto i = 0; i < mLocations.size() - 1; ++i)
	{
		for (auto j = i + 1; j < mLocations.size(); ++j)
		{
			const auto path = currentNavigationSystem->FindPathToLocationSynchronously(
				mWorld,
				mLocations[i].wayPoint->GetActorLocation(),
				mLocations[j].wayPoint->GetActorLocation()
				);
			mCostMatrix.insert(std::make_pair(std::make_pair(mLocations[i].name, mLocations[j].name), path->GetPathCost()));
			mCostMatrix.insert(std::make_pair(std::make_pair(mLocations[j].name, mLocations[i].name), path->GetPathCost()));
		}
	}
}
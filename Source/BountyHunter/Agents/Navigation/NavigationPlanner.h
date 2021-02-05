#pragma once
#include "CoreMinimal.h"
#include <NAI/include/glm/glm.hpp>
#include <NAI/include/navigation/INavigationPlanner.h>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "AI/Navigation/NavigationTypes.h"

namespace NAI {
	namespace Navigation
	{
		class INavigationPath;
	}
}

class NavigationPlanner : public NAI::Navigation::INavigationPlanner
{
private:
	struct Location
	{
		std::string name;
		AActor* wayPoint;
		
		Location() = default;
		Location(const std::string& locationName, AActor* locationWayPoint) : name { locationName }, wayPoint { locationWayPoint } {}
	};

public:
	NavigationPlanner(UWorld* world);
	~NavigationPlanner() = default;

	void GetPathFromTo(const glm::vec3& origin, const glm::vec3& destination, PathFromToCallback callback) override;
	bool FillWithLocationGivenAName(const std::string& locationName, glm::vec3& location) const override;	
	unsigned int GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const override;
	
private:
	void FindLocations();
	void CalculateCostMatrix();
	std::string GetLocationNameGivenAWayPoint(AActor* wayPoint) const;
	Location FindLocationNearest(const glm::vec3& point) const;
	void OnPathFound(uint32 aPathId, ENavigationQueryResult::Type aResultType, FNavPathSharedPtr aNavPointer);
	std::shared_ptr<NAI::Navigation::INavigationPath> CreateNavigationPath(TArray<FNavPathPoint>& pathPoints);

private:
	std::vector<Location> mLocations;
	std::map<std::pair<std::string, std::string>, unsigned int> mCostMatrix;
	PathFromToCallback mPathFromToCallback;
	UWorld* mWorld;
};

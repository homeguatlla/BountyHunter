#include "SensorVisionComponent.h"

#include "DrawDebugHelpers.h"
#include "InteractiveComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"

#include <BountyHunter/utils/UtilsLibrary.h>
#include <BountyHunter/CustomTypes.h>
#include <BountyHunter/Agents/AI/NPCAIController.h>

#include <goap/sensory/BaseSensor.h>

#include "DangerousComponent.h"

using namespace utils;

USensorVisionComponent::USensorVisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	mSensor = std::make_shared<NAI::Goap::BaseSensor>();
}

void USensorVisionComponent::BeginPlay()
{
	Super::BeginPlay();
	GetNPCAIController()->SubscribeSensor(mSensor);
}

void USensorVisionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                           FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateActorHeadLocationAndRotation();
	
	const auto forward = GetOwner()->GetActorForwardVector();
	const auto head = GetActorHeadLocation() + mActorHeadDirection * HeadDistance;
	const auto pointOfSight = head + LengthOfView * mActorHeadDirection;

	const auto channel = ECollisionChannel::ECC_VIEWABLE;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());
	
	auto hitResults = UtilsLibrary::TraceVisionSphere(
		GetWorld(),
		head,
		pointOfSight,
		Radius,
		FQuat::Identity,
		channel,
		params);

	// loop through TArray
	for (auto&& hit : hitResults)
	{
		if (GEngine) 
		{
			bool stimulusCreated = false;
			
			stimulusCreated = CheckIfIs<UInteractiveComponent>(*hit.Actor);
			stimulusCreated |= CheckIfIs<UDangerousComponent>(*hit.Actor);
			
			if(IsDebug && stimulusCreated)
			{
				auto name = hit.Actor->GetName();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *name));
				DrawDebugSphere(GetWorld(), hit.ImpactPoint, 5.0f, 10.0f, FColor::Red, false);
			}
		}			
	}
	
	//Box oriented
	if(IsDebug)
	{
		DrawDebugLines(head, pointOfSight,forward);
	}
	//TODO
	// ver como se transforma en estímulo
}

void USensorVisionComponent::UpdateActorHeadLocationAndRotation()
{
	const auto skeletalMeshComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	mActorHeadLocation = skeletalMeshComponent->GetBoneLocation(HeadBoneName);
	const auto head2 = skeletalMeshComponent->GetBoneLocation(OtherHeadBoneName);

	mActorHeadDirection = head2 - mActorHeadLocation;
}

void USensorVisionComponent::DrawDebugLines(const FVector& head, const FVector& pointOfSight, const FVector& forward) const
{
	DrawDebugSphere(GetWorld(), head, 10.0f, 20.0f, FColor::Black, false, 0.2f);
	DrawDebugSphere(GetWorld(), pointOfSight, 5.0f, 20.0f, FColor::Blue, false, 0.2f);
	DrawDebugLine(GetWorld(), head, pointOfSight, FColor::Blue, false, 0.2f);

	auto direction = pointOfSight - head;

	direction.Normalize();
	
	const auto ortogonal1 = FVector(-direction.Y, direction.X, direction.Z);
	const auto ortogonal2 = FVector::CrossProduct(direction, ortogonal1);

	std::vector<FVector> pointsFaceHead = {
		head + ortogonal1 * Radius + ortogonal2 * Radius,
		head + ortogonal1 * Radius - ortogonal2 * Radius,
		head - ortogonal1 * Radius - ortogonal2 * Radius,
		head - ortogonal1 * Radius + ortogonal2 * Radius
		};
	
	std::vector<FVector> pointsFaceSight ={
		pointOfSight + ortogonal1 * Radius + ortogonal2 * Radius,
        pointOfSight + ortogonal1 * Radius - ortogonal2 * Radius,
        pointOfSight - ortogonal1 * Radius - ortogonal2 * Radius,
        pointOfSight - ortogonal1 * Radius + ortogonal2 * Radius,
	};

	for(auto i = 0; i < 4 ; ++i)
	{
		DrawDebugLine(GetWorld(), pointsFaceHead[i], pointsFaceHead[(i+1)%4], FColor::Blue, false, 0.2f);
		DrawDebugLine(GetWorld(), pointsFaceSight[i], pointsFaceSight[(i+1)%4], FColor::Blue, false, 0.2f);
		DrawDebugLine(GetWorld(), pointsFaceHead[i], pointsFaceSight[i], FColor::Blue, false, 0.2f);
	}
}

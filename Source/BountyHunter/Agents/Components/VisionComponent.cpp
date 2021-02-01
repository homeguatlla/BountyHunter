﻿#include "VisionComponent.h"


#include "DrawDebugHelpers.h"
#include "BountyHunter/utils/UtilsLibrary.h"
#include "Components/SkeletalMeshComponent.h"
#include "BountyHunter/CustomTypes.h"
#include "Engine/Engine.h"

using namespace utils;

UVisionComponent::UVisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UVisionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const auto forward = GetOwner()->GetActorForwardVector();
	const auto head = GetActorHeadLocation() + forward * Radius;
	const auto rotation = GetOwner()->GetActorRotation();
	const auto pointOfSight = head + LengthOfView * forward;
	
	const auto channel = ECollisionChannel::ECC_VIEWABLE;
	FCollisionQueryParams params;
	params.AddIgnoredActor(GetOwner());
	
	auto hitResults = UtilsLibrary::TraceVisionSphere(GetWorld(), head, pointOfSight, Radius, FQuat::Identity, channel, params);

	DrawDebugSphere(GetWorld(), head, 10.0f, 20.0f, FColor::Black);
	DrawDebugSphere(GetWorld(), pointOfSight, 5.0f, 20.0f, FColor::Blue);
	DrawDebugLine(GetWorld(), head, pointOfSight, FColor::Blue);

	//Box oriented
	const auto halfExtend = FVector(10.0f, Radius, Radius);
	const auto halfExtendOriented = rotation.RotateVector(halfExtend);
	
	const auto halfLength = LengthOfView * forward * 0.5f;
	DrawDebugBox(GetWorld(), head, halfExtendOriented, FColor::Purple, true);
	DrawDebugBox(GetWorld(), head+halfLength, halfExtendOriented + halfLength, FColor::Red, true);

	//TODO
	// ver como se transforma en estímulo
	
	
	// loop through TArray
	for (auto&& hit : hitResults)
	{
		if (GEngine) 
		{
			// screen log information on what was hit
			auto name = hit.Actor->GetName();
			if(!name.Contains("Landscape"))
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *name));
				DrawDebugSphere(GetWorld(), hit.ImpactPoint, 5.0f, 10.0f, FColor::Red, true);
			}
		}						
	}
}

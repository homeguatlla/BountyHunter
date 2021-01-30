#include "VisionComponent.h"


#include "DrawDebugHelpers.h"
#include "BountyHunter/utils/UtilsLibrary.h"
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

	const auto head = GetOwner()->GetActorLocation();
	const auto forward = GetOwner()->GetActorForwardVector();
	const auto rotation = GetOwner()->GetActorRotation();
	const auto pointOfSight = head + LengthOfView * forward;
	//Box oriented
	const auto halfExtend = FVector(10.0f, 100.0f, 100.0f);
	const auto halfExtendOriented = rotation.RotateVector(halfExtend);
	
	const auto channel = ECollisionChannel::ECC_Visibility;
	auto hitResults = UtilsLibrary::TraceVisionBox(GetWorld(), head, pointOfSight, halfExtendOriented, FQuat::Identity, channel);

	DrawDebugSphere(GetWorld(), head, 10.0f, 20.0f, FColor::Black);
	DrawDebugSphere(GetWorld(), pointOfSight, 5.0f, 20.0f, FColor::Blue);
	DrawDebugLine(GetWorld(), head, pointOfSight, FColor::Blue);
	
	DrawDebugBox(GetWorld(), head, halfExtendOriented, FColor::Purple, true);


	// loop through TArray
	for (auto&& hit : hitResults)
	{
		if (GEngine) 
		{
			// screen log information on what was hit
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *hit.Actor->GetName()));
		}						
	}
}


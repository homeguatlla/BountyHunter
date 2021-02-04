#include "VisionComponent.h"

#include "DrawDebugHelpers.h"
#include "InteractableComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"

#include <BountyHunter/utils/UtilsLibrary.h>
#include <BountyHunter/CustomTypes.h>
#include <BountyHunter/Agents/AI/NPCAIController.h>

#include <goap/sensory/BaseSensor.h>

using namespace utils;

UVisionComponent::UVisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	mSensor = std::make_shared<NAI::Goap::BaseSensor>();
}

void UVisionComponent::BeginPlay()
{
	Super::BeginPlay();
	GetNPCAIController()->SubscribeSensor(mSensor);
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

	// loop through TArray
	for (auto&& hit : hitResults)
	{
		if (GEngine) 
		{
			const auto interactableComponent = hit.Actor->FindComponentByClass<UInteractableComponent>();
			if(interactableComponent != nullptr)
			{
				const auto stimulus = interactableComponent->CreateStimulus();
				mSensor->NotifyAll(stimulus);
				UE_LOG(LogTemp, Log, TEXT("[UVisionComponent::TickComponent] Food detected"));
	
				if(IsDebug)
				{
					auto name = hit.Actor->GetName();
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Result: %s"), *name));
					DrawDebugSphere(GetWorld(), hit.ImpactPoint, 5.0f, 10.0f, FColor::Red, true);
				}
			}
		}			
	}
	
	//Box oriented
	if(IsDebug)
	{
		DrawDebugLines(head, pointOfSight, rotation, forward);
	}
	//TODO
	// ver como se transforma en estímulo
}

void UVisionComponent::DrawDebugLines(const FVector& head, const FVector& pointOfSight, const FRotator& rotation, const FVector& forward) const
{
	DrawDebugSphere(GetWorld(), head, 10.0f, 20.0f, FColor::Black);
	DrawDebugSphere(GetWorld(), pointOfSight, 5.0f, 20.0f, FColor::Blue);
	DrawDebugLine(GetWorld(), head, pointOfSight, FColor::Blue);

	const auto halfExtend = FVector(10.0f, Radius, Radius);
	const auto halfExtendOriented = rotation.RotateVector(halfExtend);
	
	const auto halfLength = LengthOfView * forward * 0.5f;
	DrawDebugBox(GetWorld(), head, halfExtendOriented, FColor::Purple, true);
	DrawDebugBox(GetWorld(), head+halfLength, halfExtendOriented + halfLength, FColor::Red, true);
}

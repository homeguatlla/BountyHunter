// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <memory>
#include <BountyHunter/Agents/AI/IAgentAIController.h>
#include <BountyHunter/Agents/Navigation/NavigationPlanner.h>
#include <BountyHunter/Agents/NPCTypes.h>

#include <goap/IPredicate.h>
#include <goap/sensory/IStimulus.h>
#include <goap/sensory/SensorySystem.h>

#include "NPCAIController.generated.h"

namespace NAI { namespace Goap {
	class BaseSensor;
	class IAgent; } }

UCLASS()
class BOUNTYHUNTER_API ANPCAIController : public AAIController, public IAgentAIController
{
	GENERATED_BODY()
	
	public:
		void BeginPlay() override;
		void Tick(float DeltaTime) override;
		void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

		FVector GetPosition() const override;
		void MoveTo(float elapsedTime, const FVector& point) override;
		
		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Agent Controller")
		FString GetAgentName() const;
		virtual FString GetAgentName_Implementation() const;

		UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Agent Controller")
		FString GetAgentCurrentState() const;
		virtual FString GetAgentCurrentState_Implementation() const;

		void AddNewPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate);
		void SubscribeSensor(std::shared_ptr<NAI::Goap::BaseSensor> sensor) const;

private:
		void CreateAgent(NPCTypes type);
		void CreateNavigationPlanner();

		std::shared_ptr<NAI::Goap::IAgent> mAgent;
		std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> mSensorySystem;
		std::shared_ptr<NAI::Navigation::INavigationPlanner> mNavigationPlanner;
		FVector mLastPoint { FVector::ZeroVector} ;
};

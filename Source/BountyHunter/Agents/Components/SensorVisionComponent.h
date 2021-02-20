// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NPCAgentComponent.h"
#include "Components/ActorComponent.h"
#include <goap/sensory/BaseSensor.h>

#include "SensorVisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API USensorVisionComponent : public UNPCAgentComponent
{
	GENERATED_BODY()

public:
	USensorVisionComponent();

	/** Radius of the sphere volume to propagate from head to length of view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	float Radius;
	
	/** Head distance in the direction of view to put the eyes. Where view volume start. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	float HeadDistance;
	
	/** Length of view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	int LengthOfView;

	/** Head Position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	FName HeadBoneName;

	/** Next or previous bone to Head to calculate the view direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	FName OtherHeadBoneName;
	
	/** If true, draw debug lines */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	bool IsDebug;

	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

private:
	FVector GetActorHeadLocation() const { return mActorHeadLocation; }
	void UpdateActorHeadLocationAndRotation();
	void DrawDebugLines(const FVector& head, const FVector& pointOfSight, const FVector& forward) const;

	std::shared_ptr<NAI::Goap::BaseSensor> mSensor;
	FVector mActorHeadLocation;
	FVector mActorHeadDirection;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NPCAgentComponent.h"
#include "Components/ActorComponent.h"
#include "VisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UVisionComponent : public UNPCAgentComponent
{
	GENERATED_BODY()

public:
	UVisionComponent();

	/** Radius of the sphere volume to propagate from head to length of view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	float Radius;
	
	/** Length of view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	int LengthOfView;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

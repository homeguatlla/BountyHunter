// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IHomeComponent.h"
#include "NPCAgentComponent.h"
#include "HomeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UHomeComponent : public UNPCAgentComponent, public IIHomeComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHomeComponent();

	void SetGoingHome(bool isGoingHome) override { mIsGoingHome = isGoingHome; }
	bool IsGoingHome() const override { return mIsGoingHome; }
	FString GetHomeName() const override { return LocationName; }

	/** Home location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Home Attributes")
	FString LocationName;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool mIsGoingHome;
};

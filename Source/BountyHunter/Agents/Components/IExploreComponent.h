#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IExploreComponent.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UIExploreComponent : public UInterface
{
	GENERATED_BODY()
};

class IIExploreComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Explore Component")
    virtual void SetExplore(bool isExploring) = 0;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Explore Component")
    virtual bool IsExploring() const = 0;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Explore Component")
    virtual float GetExplorationRadius() const = 0;
	
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Explore Component")
    virtual float GetWaitingTimeBetweenLocations() const = 0;
};
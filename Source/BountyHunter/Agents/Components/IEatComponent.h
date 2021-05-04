#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEatComponent.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UIEatComponent : public UInterface
{
	GENERATED_BODY()
};

class IIEatComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Eat Component")
    virtual bool HasHungry() const = 0;
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Eat Component")
    virtual bool IsEating() const = 0;
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Eat Component")
	virtual void Eat(uint8 amount) = 0;
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Eat Component")
    virtual float GetMinDistanceToEat() const = 0;
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Eat Component")
	virtual void Cancel() = 0;
};
#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IHomeComponent.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UIHomeComponent : public UInterface
{
	GENERATED_BODY()
};

class IIHomeComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Home Component")
    virtual void SetGoingHome(bool isGoingHome) = 0;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Home Component")
    virtual bool IsGoingHome() const = 0;

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Home Component")
    virtual FString GetHomeName() const = 0;
};
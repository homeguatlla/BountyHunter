#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IEscapeComponent.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UIEscapeComponent : public UInterface
{
	GENERATED_BODY()
};

class IIEscapeComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Escape Component")
	virtual bool IsEscaping() const = 0;
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Escape Component")
	virtual void SetEscaping(bool isEscaping) = 0;
};
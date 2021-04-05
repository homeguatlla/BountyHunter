#pragma once
#include "INPCCharacter.h"
#include "NPCTypes.h"
#include "Components/IEatComponent.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class ANPCCharacter : public ACharacter, public TLN::INPCCharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	TEnumAsByte<NPCTypes> mType;

	TEnumAsByte<NPCTypes> GetNPCType() { return mType; }

	float GetMovementSpeed() const override;
	bool IsEating() const override;
	bool IsExploring() const override;
private:
	template<class TComponent, class IComponent, class UIComponent>
	TScriptInterface<IComponent> GetComponent() const;
};

template <class TComponent, class IComponent, class UIComponent>
TScriptInterface<IComponent> ANPCCharacter::GetComponent() const
{
	/*
	const auto eatComponent = FindComponentByClass<UEatComponent>();
	check(eatComponent != nullptr && eatComponent->GetClass()->ImplementsInterface(UIEatComponent::StaticClass()));

	if(!eatComponent)
	{
	return false;
	}
	else
	{
	const auto eatInterface = TScriptInterface<IIEatComponent>(eatComponent);
	return eatInterface->IsEating();
	}*/
	const auto component = FindComponentByClass<TComponent>();
	//check(component != nullptr && component->GetClass()->ImplementsInterface(UIComponent::StaticClass()));

	if(component)
	{
		return TScriptInterface<IComponent>(component);
	}

	return nullptr;
}

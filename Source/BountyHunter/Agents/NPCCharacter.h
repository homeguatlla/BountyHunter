#pragma once
#include "INPCCharacter.h"
#include "NPCTypes.h"
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
};

#pragma once
#include "NPCTypes.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	TEnumAsByte<NPCTypes> mType;

	TEnumAsByte<NPCTypes> GetNPCType() { return mType; }
};

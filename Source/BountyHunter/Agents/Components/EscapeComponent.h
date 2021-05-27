﻿#pragma once
#include "IEscapeComponent.h"
#include "NPCAgentComponent.h"
#include "EscapeComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UEscapeComponent : public UNPCAgentComponent, public IIEscapeComponent
{
	GENERATED_BODY()

public:
	UEscapeComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool IsEscaping() const override;

	protected:
	virtual void BeginPlay() override;	
};

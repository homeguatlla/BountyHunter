
#include "EatComponent.h"


UEatComponent::UEatComponent() :
mHasHungry{false},
mIsEating{false},
mAmount{0}
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UEatComponent::Eat(unsigned amount)
{
	mAmount = amount;
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UEatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}


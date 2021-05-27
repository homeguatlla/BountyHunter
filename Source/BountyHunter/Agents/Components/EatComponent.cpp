
#include "EatComponent.h"
#include "BountyHunter/Agents/AI/NPCAIController.h"
#include "BountyHunter/Agents/AI/Goals/EatGoal.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "goap/BasePredicate.h"


UEatComponent::UEatComponent() :
AccumulatedTimeToStartHavingHungry{1.0f},
mAmount{0},
mEatingTime{0.0f}
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UEatComponent::BeginPlay()
{
	Super::BeginPlay();

	auto controller = GetNPCAIController();
	controller->AddNewGoal(std::make_shared<EatGoal>(this));
}

void UEatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsEating())
	{
		UpdateEating(DeltaTime);
	}
	else if(!HasHungry())
	{
		UpdateHungry(DeltaTime);
	}
}

void UEatComponent::Eat(uint8 amount)
{
	check(amount > 0);
	UE_LOG(LogTemp, Log, TEXT("[UEatComponent::Eat] %s is starting eating"), *GetOwner()->GetName());
	mAmount = amount;
	//SetComponentTickEnabled(true);
	mEatingTime = EatingSpeed;
}

void UEatComponent::Cancel()
{
	mEatingTime = 0.0f;
}

void UEatComponent::UpdateEating(float elapsedTime)
{
	mEatingTime -= elapsedTime;
	UE_LOG(LogTemp, Log, TEXT("[UEatComponent::UpdateEating] %s is eating... %f"), *GetOwner()->GetName(), mEatingTime);
	if(mEatingTime <= 0.0f)
	{
		mAmount--;
		AccumulatedTimeToStartHavingHungry += TimeWithoutHungryPerAmountEaten;
		mEatingTime = mAmount <= 0 ? mEatingTime = 0.0f : mEatingTime = EatingSpeed;
		UE_LOG(LogTemp, Log, TEXT("[UEatComponent::UpdateEating] %s is finishing eating amount %f, %f"), *GetOwner()->GetName(), AccumulatedTimeToStartHavingHungry, mEatingTime);
	}
}

void UEatComponent::UpdateHungry(float elapsedTime)
{
	AccumulatedTimeToStartHavingHungry -= elapsedTime;
	//UE_LOG(LogTemp, Log, TEXT("[UEatComponent::UpdateHungry] making hungry...%f"), AccumulatedTimeToStartHavingHungry);
		
	if(AccumulatedTimeToStartHavingHungry <= 0.0f)
	{
		AddHungryPredicateToAgent();
		//UE_LOG(LogTemp, Log, TEXT("[UEatComponent::UpdateHungry] adding Hungry predicate"));
	}
}

void UEatComponent::AddHungryPredicateToAgent() const
{
	auto controller = GetNPCAIController();
	controller->AddNewPredicate(std::make_shared<NAI::Goap::BasePredicate>(IM_HUNGRY_PREDICATE_ID, IM_HUNGRY_PREDICATE_NAME));
}


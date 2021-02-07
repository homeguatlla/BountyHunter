#pragma once
#include <typeinfo>

#include "VisionStimulus.h"


class FoodStimulus : public VisionStimulus
{
public:
	FoodStimulus(int id, const glm::vec3& position, unsigned int amount, AActor* actor) :
		VisionStimulus(id, position, actor), mAmount { amount } {}
	virtual ~FoodStimulus() = default;

	std::string GetClassName() const override { return typeid(FoodStimulus).name(); }
	unsigned int GetAmount() const { return mAmount; }

private:
	unsigned int mAmount;
};

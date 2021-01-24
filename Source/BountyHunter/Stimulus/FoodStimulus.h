#pragma once
#include "VisionStimulus.h"

class FoodStimulus : public VisionStimulus
{
public:
	FoodStimulus(const glm::vec3& position, unsigned int amount) :
		VisionStimulus(position), mAmount { amount } {}
	virtual ~FoodStimulus() = default;

	unsigned int GetAmount() const { return mAmount; }

private:
	unsigned int mAmount;
};

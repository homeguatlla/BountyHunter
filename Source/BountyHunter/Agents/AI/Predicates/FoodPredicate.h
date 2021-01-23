#pragma once
#include <goap/BasePredicate.h>
#include <glm/glm.hpp>

class FoodPredicate : public NAI::Goap::BasePredicate
{
public:
	FoodPredicate(const glm::vec3& position, unsigned int amount);
	virtual ~FoodPredicate() = default;

	glm::vec3 GetPosition() const { return mPosition; }
	unsigned int GetAmount() const { return mAmount; }
	
private:
	glm::vec3 mPosition;
	unsigned int mAmount;
};

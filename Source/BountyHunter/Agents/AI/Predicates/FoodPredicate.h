#pragma once
#include <goap/BasePredicate.h>
#include <glm/glm.hpp>

#include "Chaos/KinematicGeometryParticles.h"

class FoodPredicate : public NAI::Goap::BasePredicate
{
public:
	FoodPredicate();
	FoodPredicate(const glm::vec3& position, unsigned int amount);
	virtual ~FoodPredicate() = default;

	void SetPosition(const glm::vec3& position) { mPosition = position; }
	void SetAmount(unsigned int amount) { mAmount = amount; }
	glm::vec3 GetPosition() const { return mPosition; }
	unsigned int GetAmount() const { return mAmount; }
	
private:
	glm::vec3 mPosition;
	unsigned int mAmount;
};

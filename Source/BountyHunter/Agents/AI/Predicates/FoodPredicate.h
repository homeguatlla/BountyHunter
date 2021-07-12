#pragma once
#include <goap/BasePredicate.h>
#include <glm/glm.hpp>

#include "ActorBasedPredicate.h"
#include "Chaos/KinematicGeometryParticles.h"

class AActor;

class FoodPredicate : public ActorBasedPredicate
{
public:
	FoodPredicate(int id);
	FoodPredicate(int id, const glm::vec3& position, unsigned int amount, TWeakObjectPtr<AActor> actor);
	virtual ~FoodPredicate() = default;

	void SetAmount(unsigned int amount) { mAmount = amount; }
	unsigned int GetAmount() const { return mAmount; }
	
private:
	unsigned int mAmount;
};

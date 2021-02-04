#pragma once
#include <goap/BasePredicate.h>
#include <glm/glm.hpp>

#include "Chaos/KinematicGeometryParticles.h"

class AActor;

class FoodPredicate : public NAI::Goap::BasePredicate
{
public:
	FoodPredicate(int id);
	FoodPredicate(int id, const glm::vec3& position, unsigned int amount, TWeakObjectPtr<AActor> actor);
	virtual ~FoodPredicate() = default;

	void SetPosition(const glm::vec3& position) { mPosition = position; }
	void SetAmount(unsigned int amount) { mAmount = amount; }
	glm::vec3 GetPosition() const { return mPosition; }
	unsigned int GetAmount() const { return mAmount; }
	TWeakObjectPtr<AActor> GetActor() const { return mActor; }
	bool IsActorAlive() const { return mActor.IsValid(); }

private:
	glm::vec3 mPosition;
	unsigned int mAmount;
	TWeakObjectPtr<AActor> mActor;
};

#pragma once
#include <goap/BasePredicate.h>
#include <glm/glm.hpp>

#include "ActorBasedPredicate.h"
#include "Chaos/KinematicGeometryParticles.h"

class AActor;

class EscapePredicate : public ActorBasedPredicate
{
public:
	EscapePredicate(int id);
	EscapePredicate(int id, const glm::vec3& position, TWeakObjectPtr<AActor> actor);
	virtual ~EscapePredicate() = default;
};

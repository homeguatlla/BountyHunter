#pragma once
#include <goap/BasePredicate.h>
#include <glm/glm.hpp>

class AActor;

class ActorBasedPredicate : public NAI::Goap::BasePredicate
{
public:
	ActorBasedPredicate(int id, const std::string& text);
	ActorBasedPredicate(int id, const std::string& text, const glm::vec3& position, TWeakObjectPtr<AActor> actor);
	virtual ~ActorBasedPredicate() = default;

	void SetPosition(const glm::vec3& position) { mPosition = position; }
	glm::vec3 GetPosition() const { return mPosition; }
	TWeakObjectPtr<AActor> GetActor() const { return mActor; }
	bool IsActorAlive() const { return mActor.IsValid(); }

private:
	glm::vec3 mPosition;
	TWeakObjectPtr<AActor> mActor;
};

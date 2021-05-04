#pragma once
#include <goap/sensory/IStimulus.h>

#include "GameFramework/Actor.h"

class AActor;

class SoundStimulus : public NAI::Goap::IStimulus
{
public:
	SoundStimulus(int id, const glm::vec3& position);

	virtual ~SoundStimulus() = default;

	std::string GetClassName() const override {return typeid(SoundStimulus).name();}
	glm::vec3 GetPosition() const override { return mPosition; }
	float GetDurationInMemory() const override{ return 30.f; }
	unsigned int GetId() const override { return mId;}

private:
	int mId;
	glm::vec3 mPosition;
};

#pragma once
#include <goap/sensory/IStimulus.h>

class VisionStimulus : public NAI::Goap::IStimulus
{
	static int IDCounter;

public:
	VisionStimulus(const glm::vec3& position);

	virtual ~VisionStimulus() = default;

	glm::vec3 GetPosition() const override { return mPosition; }
	float GetDurationInMemory() const override{ return 60.f; }
	unsigned int GetId() const override { return mId;}
	
private:
	int mId;
	glm::vec3 mPosition;
};

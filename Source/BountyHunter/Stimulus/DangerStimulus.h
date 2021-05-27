
#include "goap/sensory/IStimulus.h"

class DangerStimulus :  public NAI::Goap::IStimulus
{
public:
	DangerStimulus(int id, const glm::vec3& position, AActor* actor);
	virtual ~DangerStimulus() = default;

	std::string GetClassName() const override { return typeid(DangerStimulus).name(); }
	glm::vec3 GetPosition() const override { return mPosition; }
	float GetDurationInMemory() const override{ return 60.f; }
	unsigned int GetId() const override { return mId;}
	bool IsActorAlive() const { return mActor.IsValid(); }
	TWeakObjectPtr<AActor> GetActor() const { return mActor; }

private:
	int mId;
	glm::vec3 mPosition;
	TWeakObjectPtr<AActor> mActor;
};

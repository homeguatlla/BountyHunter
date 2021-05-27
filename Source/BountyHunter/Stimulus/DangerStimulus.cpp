#include "DangerStimulus.h"

DangerStimulus::DangerStimulus(int id, const glm::vec3& position, AActor* actor) :
mId{id},
mPosition{position},
mActor{actor}
{
}

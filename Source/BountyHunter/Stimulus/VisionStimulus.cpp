#include "VisionStimulus.h"

int VisionStimulus::IDCounter = 0;

VisionStimulus::VisionStimulus(const glm::vec3& position)  : mId{IDCounter++}, mPosition{position}
{
}

#include "SoundThreshold.h"


#include "BountyHunter/Stimulus/SoundStimulus.h"
#include "goap/sensory/IStimulus.h"

bool SoundThreshold::IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const
{
	//TODO además de determinar si está en rango, igual debería aprovechar para determinar
	//si el sonido es peligroso por ejemplo. El sonido de por sí debería tener una categoría
	//Sonido que conlleva peligro. Pero igual, según este threshold al tipo no le asusta y se puede
	//marcar como que no lleva peligro. No sé donde debería estar pero quizá es aquí.
	const auto soundStimulus = std::static_pointer_cast<SoundStimulus>(stimulus);
	return true; //soundStimulus->GetAmplitude() > 0;
}

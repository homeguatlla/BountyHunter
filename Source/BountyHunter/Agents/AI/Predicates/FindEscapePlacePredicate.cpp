#include "FindEscapePlacePredicate.h"
#include "Predicates.h"

FindEscapePlacePredicate::FindEscapePlacePredicate(int id, std::vector<std::shared_ptr<DangerStimulus>> stimulusList) :
BasePredicate(id, FIND_ESCAPE_PLACE_PREDICATE_NAME),
mStimulusList{stimulusList}
{
}

void FindEscapePlacePredicate::PerformActionForEachDangerousStimulus(
	std::function<void(std::shared_ptr<DangerStimulus> dangerStimulus)> action)
{
	for(auto&& dangerStimulus : mStimulusList)
	{
		action(dangerStimulus);
	}
}


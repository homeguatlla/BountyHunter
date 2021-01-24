#include "ImHungryPredicate.h"
#include "Predicates.h"

ImHungryPredicate::ImHungryPredicate() : BasePredicate(IM_HUNGRY_PREDICATE_NAME)
{
}

bool ImHungryPredicate::HasHungry(std::shared_ptr<NAI::Goap::IAgent> agent) const
{
	//TODO Given an Agent we need to know if it has a eat component and then ask
	//if has hungry. Pero está por ver.
	
	return false;
}

#include "EscapePredicate.h"
#include "Predicates.h"

EscapePredicate::EscapePredicate(int id) :
ActorBasedPredicate(id, ESCAPE_PREDICATE_NAME)
{
}

EscapePredicate::EscapePredicate(int id, const glm::vec3& position, TWeakObjectPtr<AActor> actor) :
ActorBasedPredicate(id, ESCAPE_PREDICATE_NAME)
{
}

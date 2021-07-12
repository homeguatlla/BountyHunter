#include "ActorBasedPredicate.h"
#include "Predicates.h"

ActorBasedPredicate::ActorBasedPredicate(int id, const std::string& text) :
BasePredicate(id, text),
mPosition{0.0f},
mActor{nullptr}
{
}

ActorBasedPredicate::ActorBasedPredicate(int id, const std::string& text, const glm::vec3& position, TWeakObjectPtr<AActor> actor) :
BasePredicate(id, text),
mPosition{ position },
mActor{actor}
{
}

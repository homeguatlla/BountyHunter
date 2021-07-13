#include "FoodPredicate.h"
#include "Predicates.h"

FoodPredicate::FoodPredicate(int id) :
ActorBasedPredicate(id, FOOD_PREDICATE_NAME),
mAmount{0}
{
}

FoodPredicate::FoodPredicate(int id, const glm::vec3& position, unsigned int amount, TWeakObjectPtr<AActor> actor) :
ActorBasedPredicate(id, FOOD_PREDICATE_NAME, position, actor),
mAmount{amount}
{
}

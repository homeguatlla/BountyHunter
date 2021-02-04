#include "FoodPredicate.h"
#include "Predicates.h"

FoodPredicate::FoodPredicate(int id) :
BasePredicate(id, FOOD_PREDICATE_NAME),
mPosition{0.0f},
mAmount{0},
mActor{nullptr}
{
}

FoodPredicate::FoodPredicate(int id, const glm::vec3& position, unsigned int amount, TWeakObjectPtr<AActor> actor) :
BasePredicate(id, FOOD_PREDICATE_NAME),
mPosition{ position },
mAmount{amount},
mActor{actor}
{
}

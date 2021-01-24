#include "FoodPredicate.h"
#include "Predicates.h"

FoodPredicate::FoodPredicate() :
BasePredicate(FOOD_PREDICATE_NAME),
mPosition{0.0f},
mAmount{0}
{
}

FoodPredicate::FoodPredicate(const glm::vec3& position, unsigned int amount) :
BasePredicate(FOOD_PREDICATE_NAME),
mPosition{ position },
mAmount{amount}
{
}

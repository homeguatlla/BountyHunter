#include "FoodPredicate.h"
#include "Predicates.h"

FoodPredicate::FoodPredicate(const glm::vec3& position, unsigned int amount) :
BasePredicate(FOOD_PREDICATE),
mPosition{ position },
mAmount{amount}
{
}

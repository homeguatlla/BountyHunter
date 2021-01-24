#pragma once
#include <string>

#include "FoodPredicate.h"
#include "ImHungryPredicate.h"

const std::string IM_HUNGRY_PREDICATE_NAME("IM_HUNGRY");
static std::shared_ptr<ImHungryPredicate> IM_HUNGRY_PREDICATE = std::make_shared<ImHungryPredicate>();

const std::string FOOD_PREDICATE_NAME("FOOD");
static std::shared_ptr<FoodPredicate> FOOD_PREDICATE = std::make_shared<FoodPredicate>();


#pragma once
#include "goap/BasePredicate.h"
#include "goap/predicates/GoToPredicate.h"
#include <string>
#include <memory>

namespace NAI
{
	namespace Goap
	{
		class Predicates
		{
			public:
				static std::shared_ptr<IPredicate> PREDICATE_GO_TO;
				static std::shared_ptr<IPredicate> PREDICATE_GOT_PATH;
		};
	}
}


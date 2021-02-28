#pragma once

#include <memory>
#include <functional>
#include <glm/glm.hpp>
#include <string>

namespace NAI
{
	namespace Navigation
	{
		class INavigationPath;

		class INavigationPlanner
		{
		public:
			using PathFromToCallback = std::function<void(std::shared_ptr<NAI::Navigation::INavigationPath>)>;

			virtual ~INavigationPlanner() = default;
			virtual void GetPathFromTo(const glm::vec3& origin, const glm::vec3& destination, PathFromToCallback callback) = 0;
			virtual bool FillWithLocationGivenAName(const std::string& locationName, glm::vec3& location) const = 0;
			virtual unsigned int GetAproxCost(const glm::vec3& origin, const glm::vec3& destination) const = 0;
			virtual bool GetRandomReachablePointInRadius(const glm::vec3& from, float radius, glm::vec3& reachableLocation) const = 0;
		};
	}
}


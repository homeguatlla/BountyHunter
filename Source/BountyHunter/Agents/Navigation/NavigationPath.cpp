#include "NavigationPath.h"


void NavigationPath::AddPoint(const glm::vec3& point)
{
	mPoints.push_back(point);
}

bool NavigationPath::Empty() const
{
	return mPoints.empty();
}

bool NavigationPath::HasReachedPoint(int index, const glm::vec3& position, float precision) const
{
	const glm::vec3 positionXZ(position.x, position.y, 0.0f);
	auto pathPointXZ = GetPoint(index);
	pathPointXZ.z = 0.0f;
	
	const float distance = glm::distance(pathPointXZ, positionXZ);
	return distance < precision;
}

glm::vec3 NavigationPath::GetPoint(int index) const
{
	assert(index > 0 && index < mPoints.size());
	return mPoints[index];
}

bool NavigationPath::IsEndOfPath(int index) const
{
	return index == mPoints.size() - 1;
}
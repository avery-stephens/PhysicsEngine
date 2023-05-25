#include "AreaForce.h"
#include "../Body.h"
#include "glm/gtx/quaternion.hpp"

void AreaForce::Apply(std::vector<class Body*> bodies)
{
	for (auto body : bodies)
	{
		if (!m_body->Intersects(body)) continue;
		glm::quat q = glm::angleAxis(glm::radians(m_angle), glm::vec3{ 0, 0, 1 });
		glm::vec2 force = q * glm::vec3{ 1, 0, 0 };
		body->ApplyForce(force * m_forceMagnitude);
	}
}

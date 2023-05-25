#include "DragForce.h"
#include "../Body.h"
#include <glm/gtx/norm.hpp>

void DragForce::Apply(std::vector<class Body*> bodies)
{
	for (auto body : bodies)
	{
		if (!m_body->Intersects(body)) continue;
		if (body->velocity == glm::vec2{0,0}) continue;

		float f = 0.5f * glm::length2(body->velocity) * m_drag;
		glm::vec2 force = glm::normalize(body->velocity);
		body->ApplyForce(force * (-f));
	}
}

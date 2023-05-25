#pragma once
#include "Body.h"

namespace Integrator
{
	void ExplicitEuler(Body& body, float dt)
	{
		body.position = body.position + body.velocity * dt;
		body.velocity = body.velocity + (body.force * body.invMass) * dt;
	}

	void SemiImplicitEuler(Body& body, float dt)
	{
		body.velocity = body.velocity + (body.force * body.invMass) * dt;
		body.position = body.position + body.velocity * dt;
	}
}
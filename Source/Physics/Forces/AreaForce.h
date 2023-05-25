#pragma once
#include "ForceGenerator.h"

class AreaForce : public ForceGenerator
{
public:
	AreaForce(class Body* body, float forceMag, float angle) :
		ForceGenerator{ body },
		m_forceMagnitude{ forceMag },
		m_angle{ angle }
	{}
	void Apply(std::vector<class Body*> bodies) override;
private:
	float m_forceMagnitude{ 1 };
	float m_angle{ 0 };
};
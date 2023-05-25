#pragma once
#include "ForceGenerator.h"

class PointForce : public ForceGenerator
{
public:
	PointForce(class Body* body, float forceMagnitude) :
		ForceGenerator{ body },
		m_forceMagnitude{ forceMagnitude }
	{}
	virtual void Apply(std::vector<class Body*> bodies) override;
protected:
	float m_forceMagnitude{ 1 };
};
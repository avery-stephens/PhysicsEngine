#pragma once
#include "Test.h"

class ParticleTest : public Test
{
public:
	void Initialize();

	void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render() override;

protected:

};
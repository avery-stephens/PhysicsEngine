#pragma once
class Body;

class Joint
{
public:
	Joint(Body* bodyA, Body* bodyB, float stiffness, float restLength = 0);
	~Joint();
	
	void Step(float dt);
	void Draw(class Graphics* graphics);

protected:
	float m_restLength{ 0 };
	float m_stiffness{ 0 };

	Body* m_bodyA{ nullptr };
	Body* m_bodyB{ nullptr };
};
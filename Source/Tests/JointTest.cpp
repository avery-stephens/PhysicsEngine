#include "JointTest.h"
#include "../Physics/Shapes/Shape.h"
#include "../Physics/World.h"
#include "../Physics/Body.h"
#include "../Physics/Constraints/Joint.h"
#include "../Physics/Shapes/CircleShape.h"
#include "../Engine/Random.h"

#define CHAIN

#define SPRING_STIFFNESS 100
#define SPRING_LENGTH 2
#define BODY_DAMPING 10
#define CHAIN_SIZE 3

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(0.7f, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);

#ifdef CHAIN
	auto prevBody = m_anchor;
	for (int i = 0; i < CHAIN_SIZE; i++)
	{
		auto body = new Body(new CircleShape(0.5, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 1, Body::DYNAMIC);
		//body->gravityScale = 250;
		body->damping = BODY_DAMPING;
		m_world->AddBody(body);

		auto joint = new Joint(prevBody, body, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);

		prevBody = body;
	}
#else
	Body* prevA = nullptr;
	Body* prevB = nullptr;
	Joint* joint = nullptr;

	for (int i = 0; i < CHAIN_SIZE; i++)
	{
		auto bodyA = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 200, 100 }, { 0, 0 }, 1, Body::DYNAMIC);
		//bodyA->gravityScale = 250;
		bodyA->damping = BODY_DAMPING;
		m_world->AddBody(bodyA);

		auto bodyB = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 600, 100 }, { 0, 0 }, 1, Body::DYNAMIC);
		bodyB->gravityScale = 250;
		bodyB->damping = BODY_DAMPING;
		m_world->AddBody(bodyB);

		auto joint = new Joint(bodyA, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);

		if (prevA == prevB)
		{
			auto joint = new Joint(bodyA, m_anchor, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			auto joint2 = new Joint(bodyB, m_anchor, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint2);
		}
		else
		{
			auto joint = new Joint(bodyA, prevA, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			auto joint2 = new Joint(bodyB, prevB, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint2);

			auto joint3 = new Joint(bodyA, prevB, SPRING_LENGTH, SPRING_LENGTH);
			m_world->AddJoint(joint3);

			auto joint4 = new Joint(bodyB, prevA, SPRING_LENGTH, SPRING_LENGTH);
			m_world->AddJoint(joint4);
		}
		prevA = bodyA;
		prevB = bodyB;
	}
#endif
}

void JointTest::Update()
{
	Test::Update();
	m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
}
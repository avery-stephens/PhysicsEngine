#pragma once
#include <SDL.h>

class Time
{
public:
	Time();

	void Update();
	float TimeDelta() const { return m_deltaTime; }

	void SetFixedDeltaTime(float fixedDeltaTime) { m_fixedDeltaTime = fixedDeltaTime; }
	float GetFixedDeltaTime() const { return m_fixedDeltaTime; }

private:
	uint64_t m_prevTime{ 0 };
	float m_deltaTime{ 0 };
	float m_fixedDeltaTime{ 0 };
	float m_fps{ 0 };
};
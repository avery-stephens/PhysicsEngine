#pragma once
#include "../Engine/Graphics.h"
#include "../Engine/Input.h"
#include "../Engine/Time.h"
#include "../Engine/Random.h"
#include "../Physics/World.h"

class Test
{
public:
	Test();
	~Test();

	virtual void Initialize();
	virtual void Run();

	virtual void Update();
	virtual void FixedUpdate() = 0;

	virtual void PreRender();
	virtual void Render() = 0;
	virtual void PostRender();

	bool IsQuit() { return m_quit; }

protected:
	void UpdateEvents();

protected:
	bool m_quit{ false };
	float m_fixedTime{ 0 };

	Graphics* m_graphics{ nullptr };
	Input* m_input{ nullptr };
	Time* m_time{ nullptr };
	World* m_world{ nullptr };
};

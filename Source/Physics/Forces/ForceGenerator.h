#pragma once
#include <vector>
#include <list>

class ForceGenerator
{
public:
	ForceGenerator(class Body* body = nullptr) : m_body{ body } {}

	virtual void Apply(std::vector<class Body*> bodies) = 0;
	virtual void Draw(class Graphics* graphics);

protected:
	class Body* m_body{ nullptr };
};
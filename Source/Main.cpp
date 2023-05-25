#include "Tests/ParticleTest.h"
#include "Tests/ForceTest.h"
#include "Tests/JointTest.h"
#include "Tests/CollisionTest.h"


int main(int argc, char* argv[])
{
	Test* test = new CollisionTest();
	test->Initialize();
	while (!test->IsQuit()) { test->Run(); }
	delete test;

	return 0;
}

#pragma once
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

inline void seedRandom(int seed) { srand(seed); }

inline int random() { return rand(); }
inline int random(int max) { return random() % max; } // exclusive (0 <-> (max - 1))
inline int random(int min, int max) { return min + random((max - min) + 1); } // inclusive (min <-> max)

inline float randomf() { return (float)rand() / RAND_MAX; } // 0.0 <-> 1.0
inline float randomf(float max) { return randomf() * max; } // 0.0 <-> max
inline float randomf(float min, float max) { return min + randomf(max - min); } // min <-> max
inline glm::vec2 randomUnitCircle()
{
	glm::quat q = glm::angleAxis(randomf(glm::two_pi<float>()), glm::vec3{ 0, 0, 1 });
	return q * glm::vec3{ 1, 0, 0 };
}
#pragma once

#include <GLFW/glfw3.h>
#include <utility>
#include <vector>

#include "Vec.h"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

constexpr float SMOOTHING_FACTOR = 0.0000000001f;
constexpr float G = 0.000001f;

struct Particle {
	Vec2 position;
	Vec2 velocity;
	float mass;
	Color color;
	Particle();
};

class Engine
{
public:
	int init();
	void initParticles(int number);
	int run();
	Engine();
private:
	unsigned int frame;
	GLFWwindow* window;
	std::vector<Particle> particles;
	enum returnValues { success, GLFWwindowFailure };
	int initWindow();
	std::pair<double, unsigned int> displayFramerate(std::pair<double, unsigned int> lastDisplay);
	void calculateMotion(double timestep);
	double updatePhysics(double lastFrameTime);
	void renderFrame();
};


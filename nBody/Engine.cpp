#include "Engine.h"
#include <iostream>

Engine::Engine() : frame(0), window(nullptr) {};

Particle::Particle() : position(0, 0), velocity(0, 0), mass(1), color(255, 255, 255) {};

int Engine::initWindow() {
	glfwInit();
	window = glfwCreateWindow(WIDTH, HEIGHT, "nBody", nullptr, nullptr);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (window == nullptr) {
		return GLFWwindowFailure;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, screenWidth, screenHeight);
	return success;
}

void Engine::initParticles(int number) {  // TODO finish
	Particle particle1;
	particle1.mass = 100000;
	particles.push_back(particle1);
	Particle particle2;
	particle2.position = { .8f, 0 };
	particle2.velocity = { .0, -.2f };
	particles.push_back(particle2);
}

int Engine::init() {
	initWindow();
	glEnable(GL_POINT_SMOOTH);
	glPointSize(8.0f);
	return success;
}

std::pair<double, unsigned int> Engine::displayFramerate(std::pair<double, unsigned int> lastDisplay) {
	double currentTime = glfwGetTime();
	double delta = currentTime - lastDisplay.first;
	if (delta >= 1.0) {
		double fps = (double)(frame - lastDisplay.second) / delta;
		std::cout << "fps: " << fps << '\n';
		return std::make_pair(currentTime, frame);
	}
	return lastDisplay;
}

void Engine::calculateMotion(double timestep) {
	for (auto& mainParticle : particles) {
		Vec2 netForce = { 0, 0 };
		for (auto& otherParticle : particles) {
			Vec2 displacement = otherParticle.position - mainParticle.position;
			float gravity = (G * mainParticle.mass * otherParticle.mass) / (displacement.magnitudeSquared() + SMOOTHING_FACTOR);
			netForce += displacement * gravity;
		}
		Vec2 acceleration = netForce / mainParticle.mass;
		mainParticle.velocity += acceleration * timestep;
		mainParticle.position += mainParticle.velocity * timestep;
	}
}

double Engine::updatePhysics(double lastFrameTime) {
	double currentTime = glfwGetTime();
	double timestep = currentTime - lastFrameTime;
	calculateMotion(timestep);
	return currentTime;
}

void Engine::renderFrame() {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(Particle), &particles[0].position);
	glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(Particle), &particles[0].color);
	glDrawArrays(GL_POINTS, 0, particles.size());
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

int Engine::run() {
	std::pair<double, unsigned int> fpsDisplayDelta = std::make_pair(glfwGetTime(), frame);
	double frameTime = 0;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		fpsDisplayDelta = displayFramerate(fpsDisplayDelta);
		glClearColor(0.4f, 0.6f, 0.6f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		frameTime = updatePhysics(frameTime);
		renderFrame();

		glfwSwapBuffers(window);
		frame++;
	}
	return success;
}
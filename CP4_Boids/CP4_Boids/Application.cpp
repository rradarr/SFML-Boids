#include "Application.h"

Application::Application()
{
	windowSize = sf::Vector2i(1200, 900);
	window.create(sf::VideoMode(windowSize.x, windowSize.y), "Boids", sf::Style::Close);
	window.setFramerateLimit(60);
}

Application::~Application()
{
	window.close();
}

void Application::InitializeApplication(int population, int groups)
{
	simulation.InitializeSimulation(population, groups, &window, BoidGroupsAccess);
	control.InitializeControl(&window, BoidGroupsAccess);
}

void Application::ProcessInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}

	control.ProcessInputs();
	simulation.ProcessInput();
}

void Application::Update()
{
	control.Update();
	simulation.Update(deltaTime);
}

void Application::LateUpdate()
{
	simulation.LateUpdate();
}

void Application::Draw()
{
	window.clear();

	simulation.Draw();
	control.Draw();

	window.display();
}

bool Application::IsRunning() const
{
	return window.isOpen();
}

void Application::GetDeltaTime()
{
	deltaTime = clock.restart().asSeconds();
}

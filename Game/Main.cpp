#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Math/Math.h"
#include <chrono>

nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;
nc::FrameTimer timer;

namespace nc
{
	using clock = std::chrono::high_resolution_clock;
	using clock_duration = std::chrono::duration<clock::rep, std::nano>;
}

int main(int, char**)
{
	nc::clock::time_point start = nc::clock::now();
	double result = 0.0;
	for (size_t i = 0; i < 100; i++) { result += std::sqrt(rand() % 100); }
	nc::clock_duration duration = (nc::clock::now() - start);
	std::cout << duration.count() << std::endl;
	std::cout << duration.count() / static_cast<double>(nc::clock_duration::period::den) << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::seconds>(nc::clock::now() - start).count() << std::endl;

	renderer.Startup();
	renderer.Create("GAT150", 800, 600);
	resourceManager.Startup();
	inputSystem.Startup();

	// texture
	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("cars.png", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("background.png", &renderer);

	nc::Vector2 position{ 400, 300 };
	nc::Vector2 velocity{ 0, 0 };
	float angle{ 0 };

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		// update
		inputSystem.Update();
		timer.Tick();
		//std::cout << timer.FPS() << std::endl;
		//std::cout << timer.DeltaTime() << std::endl;

		if (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		if (inputSystem.GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle - (360.0f * timer.DeltaTime()) * velocity.Length() / 1000.0f;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle + (360.0f * timer.DeltaTime()) * velocity.Length() / 1000.0f;
		}

		// get force
		nc::Vector2 force{ 0, 0 };
		if (inputSystem.GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD) 
		{ 
			force = nc::Vector2::forward * 1500.0f; 
		}
		// point force in direction of car
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));

		// add force to velocity
		velocity = velocity + (force * timer.DeltaTime());
		velocity = velocity * 0.925f;
		// set position with velocity
		position = position + (velocity * timer.DeltaTime());

		// draw
		renderer.BeginFrame();
		
		//angle = angle + 360.0f * timer.DeltaTime();
		texture2->Draw({ 0, 0 }, { 1.0f, 1.0f }, 0);
		texture1->Draw({ 0, 16, 64, 144 }, position, { 1.0f, 1.0f }, angle);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
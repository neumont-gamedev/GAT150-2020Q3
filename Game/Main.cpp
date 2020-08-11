#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Math/Math.h"

nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;
nc::FrameTimer timer;

int main(int, char**)
{
	//nc::Timer timer;
	//// profile
	//for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
	//std::cout << timer.ElapsedSeconds() << std::endl;

	renderer.Startup();
	renderer.Create("GAT150", 800, 600);
	resourceManager.Startup();
	inputSystem.Startup();

	// texture
	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);
	nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);

	nc::Vector2 position{ 400, 300 };
	nc::Vector2 velocity;
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
		timer.Tick();
		inputSystem.Update();

		if (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED)
		{
			quit = true;
		}

		// player controller
		if (inputSystem.GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle - 180.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle + 180.0f * timer.DeltaTime();
		}
		
		nc::Vector2 force{ 0, 0 };
		if (inputSystem.GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));

		// physics
		velocity = velocity + force * timer.DeltaTime();
		velocity = velocity * 0.95f;
		position = position + velocity * timer.DeltaTime();

		// draw
		renderer.BeginFrame();
				
		background->Draw({ 0, 0 }, { 1.0f, 1.0f }, 0);

		// render sprite
		car->Draw({ 128, 120, 48, 98 }, position, { 1.0f, 1.0f }, angle);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
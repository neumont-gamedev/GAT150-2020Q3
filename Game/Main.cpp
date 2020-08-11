#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"
#include "Math/Math.h"

nc::Renderer renderer;
nc::ResourceManager resourceManager;
nc::InputSystem inputSystem;
nc::FrameTimer timer;

int main(int, char**)
{
	renderer.Startup();
	resourceManager.Startup();
	inputSystem.Startup();

	renderer.Create("GAT150", 800, 600);

	nc::Texture* background = resourceManager.Get<nc::Texture>("background.png", &renderer);
	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.png", &renderer);

	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };
	nc::Vector2 velocity{ 0, 0 };

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
		resourceManager.Update();
		inputSystem.Update();

		quit = (inputSystem.GetButtonState(SDL_SCANCODE_ESCAPE) == nc::InputSystem::eButtonState::PRESSED);

		// player controller
		if (inputSystem.GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			angle = angle + 200.0f * timer.DeltaTime();
		}

		nc::Vector2 force{ 0, 0 };
		if (inputSystem.GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
		{
			force = nc::Vector2::forward * 1000.0f;
		}
		force = nc::Vector2::Rotate(force, nc::DegreesToRadians(angle));

		// physics
		velocity = velocity + force * timer.DeltaTime();
		velocity = velocity * 0.94f;
		position = position + velocity * timer.DeltaTime();

		// draw
		renderer.BeginFrame();

		background->Draw({ 0, 0 });

		// player sprite draw
		car->Draw({ 64, 110, 60, 112 }, position, { 1, 1 }, angle);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"

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

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x + 200.0f * timer.DeltaTime();
		}

		// draw
		renderer.BeginFrame();
		
		angle = angle + 180 * timer.DeltaTime();
		background->Draw({ 0, 0 }, { 1.0f, 1.0f }, 0);
		car->Draw({ 0, 16, 64, 144 }, position, { 1.0f, 1.0f }, 0);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
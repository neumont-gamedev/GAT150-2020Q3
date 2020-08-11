#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include "Core/Timer.h"

nc::Renderer renderer;
nc::ResourceManager resourceManager;
nc::InputSystem inputSystem;
nc::FrameTimer timer;

int main(int, char**)
{
	//nc::Timer timer;
	//for (size_t i = 0; i < 1000; i++) { std::sqrt(rand() % 100); }
	//
	//std::cout << timer.ElapsedTicks() << std::endl;
	//std::cout << timer.ElapsedSeconds() << std::endl;
	// 0 <-> 1.0 (0 <-> 10000000000)


	renderer.Startup();
	resourceManager.Startup();
	inputSystem.Startup();

	renderer.Create("GAT150", 800, 600);

	nc::Texture* background = resourceManager.Get<nc::Texture>("background.bmp", &renderer);
	nc::Texture* car = resourceManager.Get<nc::Texture>("cars.bmp", &renderer);

	float angle{ 0 };
	nc::Vector2 position{ 400, 300 };

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

		if (inputSystem.GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x - 200.0f * timer.DeltaTime();
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x + 200.0f * timer.DeltaTime();
		}

		// draw
		renderer.BeginFrame();

		angle = angle + 90 * timer.DeltaTime();
		background->Draw({ 0, 0 });
		car->Draw({ 0, 16, 64, 144 }, position);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
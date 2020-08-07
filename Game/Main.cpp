#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"
#include <SDL.h>
#include <iostream>

nc::Renderer renderer;
nc::ResourceManager resourceManager;
nc::InputSystem inputSystem;

int main(int, char**)
{
	renderer.Startup();
	resourceManager.Startup();
	inputSystem.Startup();

	renderer.Create("GAT150", 800, 600);

	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);

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

		resourceManager.Update();
		inputSystem.Update();

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x - 1.0f;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x + 1.0f;
		}

		renderer.BeginFrame();

		angle = angle + 1;
		texture1->Draw(position, { 1, 1 }, angle);
		texture2->Draw({ 200, 400 }, { 2, 2 }, angle + 90);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
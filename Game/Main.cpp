#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"


nc::ResourceManager resourceManager;
nc::Renderer renderer;
nc::InputSystem inputSystem;

int main(int, char**)
{
	renderer.Startup();
	renderer.Create("GAT150", 800, 600);
	resourceManager.Startup();
	inputSystem.Startup();

	// texture
	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);

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
		inputSystem.Update();

		if (inputSystem.GetButtonState(SDL_SCANCODE_LEFT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x - 1.0f;
		}
		if (inputSystem.GetButtonState(SDL_SCANCODE_RIGHT) == nc::InputSystem::eButtonState::HELD)
		{
			position.x = position.x + 1.0f;
		}

		// draw
		renderer.BeginFrame();
		
		angle = angle + 0.5f;
		texture1->Draw({ 500, 100 }, { 3.0f, 3.0f }, angle);
		texture2->Draw(position, { 3.0f, 3.0f }, angle + 90);

		renderer.EndFrame();
	}

	inputSystem.Shutdown();
	resourceManager.Shutdown();
	renderer.Shutdown();
	SDL_Quit();

	return 0;
}
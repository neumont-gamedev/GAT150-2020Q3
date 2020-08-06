#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include <SDL.h>
#include <iostream>

nc::Renderer renderer;
nc::ResourceManager resourceManager;

int main(int, char**)
{
	renderer.Startup();
	resourceManager.Startup();

	renderer.Create("GAT150", 800, 600);

	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.bmp", &renderer);

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

		resourceManager.Update();

		renderer.BeginFrame();

		angle = angle + 1;
		texture1->Draw({ 500, 100 }, { 2, 2 }, angle);
		texture2->Draw({ 200, 400 }, { 2, 2 }, angle + 90);

		renderer.EndFrame();
	}

	resourceManager.Shutdown();
	SDL_Quit();

	return 0;
}
#include "pch.h"
#include "Graphics/Texture.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"

nc::Renderer renderer;
nc::ResourceManager resourceManager;

int main(int, char**)
{
	resourceManager.Startup();
	renderer.Startup();

	renderer.Create("GAT150", 800, 600);

	// texture
	nc::Texture* texture1 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);
	nc::Texture* texture2 = resourceManager.Get<nc::Texture>("sf2.png", &renderer);
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

		renderer.BeginFrame();

		// draw
		angle = angle + 1.0f;
		texture1->Draw({ 500, 100 }, { 3.0f, 3.0f }, angle);
		texture2->Draw({ 300, 200 }, { 2.0f, 2.0f }, angle + 90);

		renderer.EndFrame();
	}

	renderer.Shutdown();
	resourceManager.Shutdown();

	SDL_Quit();

	return 0;
}
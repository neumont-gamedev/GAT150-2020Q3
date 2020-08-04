#include "pch.h"

using u32 = unsigned int;

SDL_Texture* CreateTexture(const std::string& name, SDL_Renderer* renderer)
{
	SDL_Surface* image = SDL_LoadBMP(name.c_str());
	if (image == nullptr)
	{
		std::cout << "Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
	if (texture == nullptr)
	{
		std::cout << "Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	return texture;
}

void Destroy(SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
}

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("GAT150", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr) 
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	size_t width = 128;
	size_t height = 128;

	u32* pixels = new u32[width * height];
	memset(pixels, 255, width * height * sizeof(u32));

	SDL_Texture* texture1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(u32));

	//SDL_Surface* image = SDL_LoadBMP("girl.bmp");
	//SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, image);

	SDL_Texture* texture2 = CreateTexture("sf2.bmp", renderer);


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

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_RETURN]) {
			printf("<RETURN> is pressed.\n");
		}
		if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {
			printf("Right and Up Keys Pressed.\n");
		}

		// update texture
		for (size_t i = 0; i < width * height; i++)
		{
			unsigned char c = rand() % 256;
			pixels[i] = (c << 24 | c << 16 | c << 8);
		}
		SDL_UpdateTexture(texture1, NULL, pixels, width * sizeof(u32));

		// render
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderClear(renderer);


		{
			SDL_SetRenderDrawBlendMode(renderer, SDL_BlendMode::SDL_BLENDMODE_BLEND);
			SDL_RenderCopy(renderer, texture1, NULL, NULL);
		}

		{
			int w, h;
			SDL_QueryTexture(texture2, NULL, NULL, &w, &h);

			SDL_Rect rect;
			rect.w = w;
			rect.h = h;
			rect.x = 0;
			rect.y = 0;
			SDL_RenderCopy(renderer, texture2, NULL, &rect);
		}


		SDL_RenderPresent(renderer);

	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
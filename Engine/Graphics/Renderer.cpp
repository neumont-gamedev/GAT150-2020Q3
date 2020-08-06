#include "pch.h"
#include "Renderer.h"

namespace nc
{
	bool Renderer::Startup()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return false;
		}

		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

		return true;
	}

	void Renderer::Shutdown()
	{
		IMG_Quit();
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}

	void Renderer::Update()
	{
		//
	}

	bool Renderer::Create(const std::string& name, int width, int height)
	{
		m_window = SDL_CreateWindow("GAT150", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (m_window == nullptr)
		{
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return false;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (m_renderer == nullptr)
		{
			std::cout << "Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}

	void Renderer::BeginFrame()
	{
		SDL_RenderClear(m_renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}
}
#include "pch.h"
#include "Renderer.h"

bool Renderer::Startup()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::Shutdown()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

void Renderer::Update()
{
    //
}

bool Renderer::Create(const std::string& name, int width, int height)
{
    m_window = SDL_CreateWindow("GAT150", 100, 100, width, height, SDL_WINDOW_SHOWN);
    if (m_window == nullptr)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == nullptr)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return 1;
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

#include "pch.h"
#include "Engine.h"
#include "Graphics/Renderer.h"
#include "Resources/ResourceManager.h"
#include "Input/InputSystem.h"

namespace nc
{
    bool Engine::Startup()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        {
            std::cout << "Error: " << SDL_GetError() << std::endl;
            return false;
        }

        // add engine systems
        m_systems.push_back(new Renderer);
        m_systems.push_back(new InputSystem);
        m_systems.push_back(new ResourceManager);

        // startup engine systems
        for (auto system : m_systems)
        {
            system->Startup();
        }

        GetSystem<Renderer>()->Create("GAT150", 800, 600);

        return false;
    }

    void Engine::Shutdown()
    {
        for (auto system : m_systems)
        {
            system->Shutdown();
            delete system;
        }

        SDL_Quit();
    }

    void Engine::Update()
    {
        m_timer.Tick();
        for (auto system : m_systems)
        {
            system->Update();
        }
    }


}

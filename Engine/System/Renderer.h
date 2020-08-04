#pragma once
#include "pch.h"

class Renderer
{
public:
	bool Startup();
	void Shutdown();
	void Update();

	bool Create(const std::string& name, int width, int height);
	void BeginFrame();
	void EndFrame();

	SDL_Renderer* GetSDLRenderer() { return m_renderer; }

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
};
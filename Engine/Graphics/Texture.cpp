#include "pch.h"
#include "Texture.h"

namespace nc
{
	bool Texture::Create(const std::string& name, void* data)
	{
		SDL_Surface* surface = IMG_Load(name.c_str());
		if (surface == nullptr)
		{
			return false;
		}

		m_renderer = static_cast<SDL_Renderer*>(data);
		m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);

		SDL_FreeSurface(surface);

		return true;
	}

	void Texture::Destroy()
	{
		//
	}

	void Texture::Draw(const Vector2& position, const Vector2& scale, float angle)
	{
		Vector2 size = GetSize();
		size = size * scale;

		SDL_Rect dest;
		dest.x = static_cast<int>(position.x);
		dest.y = static_cast<int>(position.y);
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);

		SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
	}

	Vector2 Texture::GetSize() const
	{
		int w, h;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &w, &h);

		return { w, h };
	}
}

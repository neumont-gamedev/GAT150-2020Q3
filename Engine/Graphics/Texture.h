#pragma once
#include "Math/Vector2.h"
#include "Resources/Resource.h"
#include <SDL.h>
#include <string>

namespace nc
{
	class Texture : public Resource
	{
	public:
		bool Create(const std::string& name, void* renderer) override;
		void Destroy() override;

		void Draw(const Vector2& position, const Vector2& scale = Vector2::one, float angle = 0);
		void Draw(const SDL_Rect& source, const Vector2& position, const Vector2& scale = Vector2::one, float angle = 0);
		Vector2 GetSize();

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};
}


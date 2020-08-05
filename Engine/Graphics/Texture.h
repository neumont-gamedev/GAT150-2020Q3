#pragma once
#include "Resources/Resource.h"
#include "Math/Vector2.h"
#include "SDL.h"

namespace nc
{
	class Texture : public Resource
	{
	public:
		// resource
		virtual bool Create(const std::string& name, void* data) override;
		virtual void Destroy() override;

		void Draw(const Vector2& position, const Vector2& scale, float angle);
		Vector2 GetSize() const;

	protected:
		SDL_Texture* m_texture{ nullptr };
		SDL_Renderer* m_renderer{ nullptr };
	};

}


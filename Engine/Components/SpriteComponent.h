#pragma once
#include "RenderComponent.h"

namespace nc
{
	class SpriteComponent : public RenderComponent
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;

		void Read(const rapidjson::Value& value) override;

		virtual void Update() override;
		virtual void Draw() override;

	protected:
		std::string m_textureName;
		SDL_Rect m_rect{ 0, 0, 0, 0 };
	};
}
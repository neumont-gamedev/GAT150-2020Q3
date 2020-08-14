#pragma once
#include "RenderComponent.h"



namespace nc
{
	class SpriteComponent : public RenderComponent
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Read(const rapidjson::Value& value);

		virtual void Update() override;
		virtual void Draw() override;

	protected:
		std::string m_name;
		SDL_Rect m_rect;
		class Texture* m_texture;
	};
}
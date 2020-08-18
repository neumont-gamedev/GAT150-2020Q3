#pragma once
#include "RenderComponent.h"
#include "Objects/ObjectFactory.h"

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

		OBJECT_FACTORY_REGISTER_DECLARATION(SpriteComponent)

	protected:
		std::string m_textureName;
		SDL_Rect m_rect{ 0, 0, 0, 0 };
		class Texture* m_texture{ nullptr };
	};
}
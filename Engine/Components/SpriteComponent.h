#pragma once
#include "RenderComponent.h"

namespace nc
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:
		virtual void Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Update() override;
		virtual void Draw() override;

	protected:
		Texture* m_texture;
	};
}

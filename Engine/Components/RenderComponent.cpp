#include "pch.h"
#include "RenderComponent.h"

namespace nc
{
	void RenderComponent::Read(const rapidjson::Value& value)
	{
		json::Get(value, "z", m_z);
	}
}

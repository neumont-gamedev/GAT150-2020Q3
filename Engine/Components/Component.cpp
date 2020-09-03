#include "pch.h"
#include "Component.h"

namespace nc
{
	void Component::Create(void* data)
	{
		m_owner = static_cast<GameObject*>(data);
	}
}

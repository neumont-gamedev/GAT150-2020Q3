#include "pch.h"
#include "ResourceManager.h"

bool nc::ResourceManager::Startup()
{
    return true;
}

void nc::ResourceManager::Shutdown()
{
    for (auto resource : m_resources)
    {
        resource.second->Destroy();
        delete resource.second;
    }
}

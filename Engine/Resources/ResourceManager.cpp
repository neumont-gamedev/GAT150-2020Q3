#include "pch.h"
#include "ResourceManager.h"

namespace nc
{
    bool ResourceManager::Startup()
    {
        return true;
    }

    void ResourceManager::Shutdown()
    {
        RemoveAll();
    }

    void ResourceManager::Update()
    {
        //
    }

    void ResourceManager::Remove(const std::string& name)
    {
        auto iter = m_resources.find(name);
        if (iter != m_resources.end())
        {
            iter->second->Destroy();
            delete iter->second;

            m_resources.erase(iter);
        }
    }

    void ResourceManager::RemoveAll()
    {
        for (auto resource : m_resources)
        {
            resource.second->Destroy();
            delete resource.second;
        }
    }
}

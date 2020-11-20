#include "..\Headers\ComponentManager.h"


USING(Engine)
IMPLEMENT_SINGLETON(ComponentManager)

ComponentManager::ComponentManager()
{
}

HRESULT ComponentManager::ReserveSizePrototypeContainer(_int iSceneCount)
{
    if (0 > iSceneCount)
        return E_FAIL;

    m_iSceneCount = iSceneCount;
    m_pPrototypes = new PROTOTYPES[m_iSceneCount];
    if (nullptr == m_pPrototypes)
    {
        LOG_MSG(L"Error", L"ReserveSizePrototypeContainer has Failed.");
        return E_FAIL;
    }

    return S_OK;
}

HRESULT ComponentManager::AddComponentPrototype(
    _int iSceneIndex,
    const wstring& ComponentTag,
    Component* pPrototype)
{
    if (0 > iSceneIndex || m_iSceneCount <= iSceneIndex)
    {
        LOG_MSG(L"Error", L"Component PrototypeContainer Out of range");
        return E_FAIL;
    }

    auto iter_find = m_pPrototypes[iSceneIndex].find(ComponentTag);
    if (m_pPrototypes[iSceneIndex].end() == iter_find)
    {
        m_pPrototypes[iSceneIndex].insert(make_pair(ComponentTag, pPrototype));
    }

    return S_OK;
}

Component* ComponentManager::CloneComponentPrototype(
    _int iSceneIndex,
    const wstring& ComponentTag,
    void* pArg)
{
    if (0 > iSceneIndex || m_iSceneCount <= iSceneIndex)
    {
        LOG_MSG(L"Error", L"Component PrototypeContainer Out of range");
        return nullptr;
    }
    
    auto iter_find = m_pPrototypes[iSceneIndex].find(ComponentTag);
    if (m_pPrototypes[iSceneIndex].end() == iter_find)
    {
        WCHAR szBuffer[128] = L"";

        swprintf_s(szBuffer, L"Not found %s Prototype", ComponentTag.c_str());

        LOG_MSG(L"Warning", szBuffer);
        return nullptr;
    }
    
    return iter_find->second->Clone(pArg);
}

HRESULT ComponentManager::ClearForScene(_int iSceneIndex)
{
    if (0 > iSceneIndex || m_iSceneCount <= iSceneIndex)
    {
        LOG_MSG(L"Error", L"Component PrototypeContainer Out of range");
        return E_FAIL;
    }

    for (auto& Pair : m_pPrototypes[iSceneIndex])
    {
        SafeRelease(Pair.second);
    }
    m_pPrototypes[iSceneIndex].clear();

    return S_OK;
}

void ComponentManager::Free()
{
    for (_int i = 0; i < m_iSceneCount; ++i)
    {
        for (auto& Pair : m_pPrototypes[i])
        {
            SafeRelease(Pair.second);
        }
        m_pPrototypes[i].clear();
    }

    SafeDeleteArray(m_pPrototypes);
}
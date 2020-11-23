#include "..\Headers\GameObject.h"
#include "Management.h"

USING(Engine)

GameObject::GameObject(_lpd3dd9 _pDevice)
    : m_pDevice(_pDevice)
{
    SafeAddRef(m_pDevice);
}

GameObject::GameObject(const GameObject& other)
    : m_pDevice(other.m_pDevice)
{
    SafeAddRef(m_pDevice);
}

HRESULT GameObject::ReadyGameObjectPrototype()
{
    return S_OK;
}

HRESULT GameObject::ReadyGameObject(void* _pArg)
{
    return S_OK;
}

_uint GameObject::UpdateGameObject(DOUBLE _fDeltaTime)
{
    return _uint();
}

_uint GameObject::LateUpdateGameObject(DOUBLE _fDeltaTime)
{
    return _uint();
}

HRESULT GameObject::RenderGameObject()
{
    return S_OK;
}

void GameObject::Free()
{
    SafeRelease(m_pDevice);

    for (auto& pair : m_Components)
    {
        SafeRelease(pair.second);
    }

    m_Components.clear();
}

HRESULT GameObject::AddComponent(
    int iSceneIndex, 
    const wstring& PrototypeTag, 
    const wstring& ComponentTag, 
    Component** ppComponent, 
    void* pArg)
{
    auto pManagement = Management::Get_Instance();
    if (nullptr == pManagement)
        return E_FAIL;

    Component* pClone = pManagement->CloneComponentPrototype(iSceneIndex, PrototypeTag, pArg);
    if (nullptr == pClone)
        return E_FAIL;
    
    m_Components.insert(make_pair(ComponentTag, pClone));

    if (ppComponent)
    {
        *ppComponent = pClone;
        SafeAddRef(pClone);
    }

    return S_OK;
}

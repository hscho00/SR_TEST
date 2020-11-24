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

Component* GameObject::GetComponent(const wstring& ComponentTag)
{
    auto iter_find = m_Components.find(ComponentTag);
    if (m_Components.end() == iter_find)
        return nullptr;
    return iter_find->second;
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

    // 프로토 타입의 컴포넌트를 프로토타입 오브젝트의 컴포넌트 리스트에 추가하는 방식
    
    return S_OK;
}

#include "..\Headers\GameObject.h"

USING(Engine)
GameObject::GameObject(_lpd3dd9 _pDevice)
{
}

HRESULT GameObject::ReadyGameObjectPrototype()
{
    return E_NOTIMPL;
}

HRESULT GameObject::ReadyGameObject(void* _pArg)
{
    return E_NOTIMPL;
}

_uint GameObject::UpdateGameObject(float _fDeltaTime)
{
    return _uint();
}

_uint GameObject::LateUpdateGameObject(float _fDeltaTime)
{
    return _uint();
}

HRESULT GameObject::RenderGameObject()
{
    return E_NOTIMPL;
}

GameObject* GameObject::Clone(void* _pArg)
{
    return nullptr;
}

void GameObject::Free()
{
}

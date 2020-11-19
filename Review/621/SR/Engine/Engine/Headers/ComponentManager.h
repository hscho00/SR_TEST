#pragma once
#ifndef __COMPONENTMANAGER_H__
#define __COMPONENTMANAGER_H__

#include "Base.h"
#include "Component.h"

BEGIN(Engine)
class ComponentManager :
    public CBase
{
    DECLARE_SINGLETON(ComponentManager)

private:
    ComponentManager();
    virtual ~ComponentManager() = default;

public:
    HRESULT ReserveSizePrototypeContainer(_int iSceneCount);
    HRESULT AddComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, Component* pPrototype);
    Component* CloneComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, void* pArg = nullptr);
    HRESULT ClearForScene(_int iSceneIndex);

public:
    virtual void Free() override;

private:
    typedef unordered_map<wstring, Component*> PROTOTYPES;
    PROTOTYPES* m_pPrototypes = nullptr;
    _int m_iSceneCount = 0;
};
END

#endif // ! __COMPONENTMANAGER_H__



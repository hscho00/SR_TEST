#pragma once

#ifndef __COMPONENTMANAGER_H__

#include "Base.h"
#include "Component.h"

BEGIN(Engine)
class CComponentManager : public CBase
{
	DECLARE_SINGLETON(CComponentManager)
public:
	CComponentManager();
	virtual ~CComponentManager() = default;

public:
	HRESULT ReserveSizePrototypeContainer(_int iSceneCount);
	HRESULT AddComponentprototype(_int iSceneIndex, const wstring& ComponentTag, CComponent* pPrototype);
	CComponent* CloneComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, void* pArg = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);


public:
	virtual void Free() override;

private:
	typedef unordered_map<wstring, CComponent*> PROTOTYPES;
	PROTOTYPES* m_pPrototypes = nullptr;
	_int m_iSceneCount = 0;
};
END

#define __COMPONENTMANAGER_H__
#endif
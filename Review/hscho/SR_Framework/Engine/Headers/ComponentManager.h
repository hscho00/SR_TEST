#pragma once
#ifndef __COMPONENTMANAGER_H__

#include "Base.h"

#include "VIBuffer_TriColor.h"
#include "VIBuffer_QuadColor.h"
//#include "Transform.h"

BEGIN(Engine)
class CComponentManager final : public CBase
{
	DECLARE_SINGLETON(CComponentManager)

private:
	CComponentManager();
	virtual ~CComponentManager() = default;

public:
	HRESULT ReservePrototypeContainer(_int iSceneCount);
	HRESULT AddComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, CComponent* pPrototype);
	CComponent* CloneComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, void* pArg = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);

public:
	virtual void Free() override;

private:
	typedef unordered_map<wstring, CComponent*> PROTOTYPES;
	PROTOTYPES* m_pPrototypes;
	_int m_iSceneCount;

};
END

#define __COMPONENTMANAGER_H__
#endif
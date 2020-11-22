#pragma once
#ifndef __GAMEOBJECTMANAGER_H__

#include "Base.h"
#include "GameObject.h"
#include "Layer.h"

BEGIN(Engine)
class CGameObjectManager final : public CBase
{
	DECLARE_SINGLETON(CGameObjectManager)

private:
	CGameObjectManager();
	virtual ~CGameObjectManager() = default;

public:
	// ReadyEngine()
	HRESULT ReserveContainer(_int iSceneCount, _bool isUseStaticScene = false, _int iStaticScene = 0);
	
	//
	HRESULT AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, CGameObject* pPrototype);

	HRESULT AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity);
	HRESULT AddGameObjectInLayer(_int iFromSceneIndex, const wstring& GameObjectTag, _int iToSceneIndex, const wstring& LayerTag, void* pArg = nullptr);
	
	HRESULT ClearForScene(_int iSceneIndex);

	CGameObject* GetGameObjectInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx);
	// + 나중에 idx 말고 GameObjectTag, using 여부도 체크해서 오브젝트 찾을 수 있게 오버로딩 하자

public:
	_uint UpdateGameObject(_int iSceneIndex, float fDeltaTime);
	_uint LateUpdateGameObject(_int iSceneIndex, float fDeltaTime);

private:
	CGameObject* CloneGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, void* pArg = nullptr);

public:
	virtual void Free() override;

private:
	typedef unordered_map<wstring, CGameObject*> PROTOTYPES;
	PROTOTYPES* m_pPrototypes;

	typedef unordered_map<wstring, CLayer*> LAYERS;
	LAYERS* m_pLayers;

	_int m_iSceneCount;
	_bool m_bUseStatic;
	_int m_iStaticScene;

};
END

#define __GAMEOBJECTMANAGER_H__
#endif


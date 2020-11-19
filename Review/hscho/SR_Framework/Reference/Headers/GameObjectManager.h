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
	HRESULT ReservePrototypeContainer(_int iSceneCount);
	HRESULT AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, CGameObject* pPrototype);
	CGameObject* CloneGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, void* pArg = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);

	//
	HRESULT ReserveLayerContainer(/*_int iSceneCount,*/);	// 음.... ReservePrototypeContainer 랑 한셋트 같은데...
	HRESULT AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity);
	HRESULT AddGameObjectInLayer(_int iSceneIndex, const wstring& LayerTag, CGameObject* pClone);
	CGameObject* GetObjInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx);	// 나중에 GameObjectTag도 찾을 수 있게
	//unordered_map<wstring, CLayer*>* GetLayerOrNull(_int iSceneIndex) const;

public:
	_uint UpdateGameObject(_int iSceneIndex, float fDeltaTime);
	_uint LateUpdateGameObject(_int iSceneIndex, float fDeltaTime);

	/////////////////////////////////////////////////////
	// 렌더러 생기면 밖으로 빠질 것들
	HRESULT RenderGameObject();
	/////////////////////////////////////////////////////

public:
	virtual void Free() override;

private:
	typedef unordered_map<wstring, CGameObject*> PROTOTYPES;
	PROTOTYPES* m_pPrototypes;

	typedef unordered_map<wstring, CLayer*> LAYERS;
	LAYERS* m_pLayers;

	_int m_iSceneCount;

};
END

#define __GAMEOBJECTMANAGER_H__
#endif


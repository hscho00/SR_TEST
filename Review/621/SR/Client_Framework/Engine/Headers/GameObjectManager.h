#pragma once
#ifndef __GAMEOBJECTMANAGER_H__
#define __GAMEOBJECTMANAGER_H__

#include "Base.h"
#include "GameObject.h"

CODEBEGIN(Engine)
class GameObjectManager final : public CBase
{
	DECLARE_SINGLETON(GameObjectManager)

private:
	GameObjectManager();
	virtual ~GameObjectManager() = default;

public:
	HRESULT ReserveSizeContainer(_int iSceneCount);
	HRESULT AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, GameObject* pPrototype);
	HRESULT AddGameObjectinLayer(_int prototype_index, const wstring& gameobject_tag, _int clone_index, const wstring& layer_tag, void* pArg = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);

public:
	_uint	UpdateGameObject(DOUBLE fDeltaTime);
	_uint	LateUpdateGameObject(DOUBLE fDeltaTime);

public:
	virtual void Free() override;

private:
	GameObject* CloneGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, void* pArg = nullptr);

private:
	typedef unordered_map<wstring, GameObject*> PROTOTYPES;
	PROTOTYPES* m_pPrototypes = nullptr;

	typedef unordered_map<wstring, class Layer*>	LAYERS;
	LAYERS* m_pLayers = nullptr;

	_int m_iSceneCount = 0;

};
CODEEND

#endif // !1


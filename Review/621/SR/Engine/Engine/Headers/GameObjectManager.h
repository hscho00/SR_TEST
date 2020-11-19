#pragma once
#ifndef __GAMEOBJECTMANAGER_H__
#define __GAMEOBJECTMANAGER_H__

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)
class GameObjectManager final : public CBase
{
	DECLARE_SINGLETON(GameObjectManager)

private:
	GameObjectManager();
	virtual ~GameObjectManager() = default;

public:
	HRESULT ReserveSizePrototypeContainer(_int iSceneCount);
	HRESULT AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, GameObject* pPrototype);
	GameObject* CloneGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, void* pArg = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);

public:
	_uint	UpdateGameObject(float fDeltaTime);
	_uint	LateUpdateGameObject(float fDeltaTime);

public:
	virtual void Free() override;

private:
	typedef unordered_map<wstring, GameObject*> PROTOTYPES;
	PROTOTYPES* m_pPrototypes = nullptr;

	_int m_iSceneCount = 0;

};
END

#endif // !1


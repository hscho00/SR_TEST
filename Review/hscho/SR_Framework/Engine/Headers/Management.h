#pragma once
#ifndef __MANAGEMENT_H__

#include "Base.h"
#include "Grahpic_Device.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "TimeManager.h"


BEGIN(Engine)
class ENGINE_DLL CManagement final : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	CManagement();
	virtual ~CManagement() = default;

public:
	/* For.General */
	HRESULT ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplaymode);
	_uint UpdateEngine();
	_uint RenderEngine();

public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 GetDevice();

public:
	/* For.SceneManager */
	HRESULT SetUpCurrentScene(_int iSceneID, CScene* pCurrentScene);

public:
	/* For.Renderer */

public:
	/* For.GameObjectManager */
	HRESULT ReadyGameObjectManager(_int iSceneCount);
	HRESULT AddObjPrototype(_int iSceneIndex, const wstring & GameObjectTag, CGameObject * pPrototype);
	CGameObject* CloneObjPrototype(_int iSceneIndex, const wstring & GameObjectTag, void* pArg = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);
	HRESULT AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity);
	HRESULT AddObjInLayer(_int iSceneIndex, const wstring& LayerTag, CGameObject* pClone);
	CGameObject* GetObjInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx);
	HRESULT UpdateGameObject(_int iSceneIndex);
	HRESULT LateUpdateGameObject(_int iSceneIndex);

public:
	/* For.ComponentManager */

public:
	virtual void Free() override;
	static void ReleaseEngine();

private:
	CGraphic_Device* m_pGraphic_Dev;
	CSceneManager* m_pSceneManager;
	CGameObjectManager* m_pGameObjectManager;
	CComponentManager* m_pComponentManager;
	CTimeManager* m_pTimeManager;

	_uint m_iUpdateEvent;
};
END

#define __MANAGEMENT_H__
#endif
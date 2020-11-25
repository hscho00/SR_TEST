#pragma once
#ifndef __MANAGEMENT_H__

#include "Base.h"
#include "Grahpic_Device.h"
#include "TimeManager.h"
#include "GameObjectManager.h"
#include "SceneManager.h"
#include "ComponentManager.h"
#include "Renderer.h"


BEGIN(Engine)
class ENGINE_DLL CManagement final : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	CManagement();
	virtual ~CManagement() = default;

public:
	/* For.General */
	HRESULT ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplaymode, 
						_int iSceneCount, _bool isUseStaticScene = false, _int iStaticScene = 0);
	_uint UpdateEngine();
	_uint RenderEngine(HWND hWnd = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);

public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 GetDevice();

public:
	/* For.TimeManager */
	_float Get_DeltaTime() const;

public:
	/* For.SceneManager */
	HRESULT SetUpCurrentScene(CScene* pCurrentScene);

public:
	/* For.GameObjectManager */
	HRESULT AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, CGameObject* pPrototype);
	HRESULT AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity);
	HRESULT AddGameObjectInLayer(_int iFromSceneIndex, const wstring& GameObjectTag, _int iToSceneIndex, const wstring& LayerTag, void* pArg = nullptr);
	CGameObject* GetGameObjectInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx);

public:
	/* For.ComponentManager */
	HRESULT AddComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, CComponent* pPrototype);
	CComponent* CloneComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, void* pArg = nullptr);

public:
	/* For.Renderer */
	HRESULT AddGameObjectInRenderer(ERenderID eID, class CGameObject* pGameObject);

public:
	virtual void Free() override;
	static void ReleaseEngine();

private:
	CGraphic_Device* m_pGraphic_Dev;
	CTimeManager* m_pTimeManager;
	CGameObjectManager* m_pGameObjectManager;
	CSceneManager* m_pSceneManager;
	CComponentManager* m_pComponentManager;
	CRenderer* m_pRenderer;

	_uint m_iUpdateEvent;

};
END

#define __MANAGEMENT_H__
#endif
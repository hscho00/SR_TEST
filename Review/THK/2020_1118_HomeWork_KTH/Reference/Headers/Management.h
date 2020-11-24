#pragma once
#ifndef __MANAGEMENT_H__

#include "Base.h"
#include "Graphic_Device.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "Time_Manager.h"
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
	HRESULT ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplaymode, _uint iSceneCount);
	_uint UpdateEngine();
	_uint RenderEngine(HWND hWnd = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);
public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 GetDevice();

public:
	/* For.SceneManager */
	HRESULT SetUpCurrentScene(_int iSceneID, CScene* pCurrentScene);

public: // GameObjectManager
	HRESULT AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, CGameObject* pPrototype);
	HRESULT AddGameObjectInLayer(_int iFromSceneIndex, const wstring& GameObjectTag, _int iToSceneIndex, const wstring& LayerTag, void* pArg = nullptr);

public: // ComponentManager
	HRESULT AddComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, CComponent* pPrototype);
	CComponent* CloneComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, void* pArg = nullptr);

public: // Renderer
	HRESULT AddGameObjectInRenderer(ERenderID eID, class CGameObject* pGameObject);
public:
	virtual void Free() override;
	static void ReleaseEngine();

private:
	CGraphic_Device*	m_pGraphic_Dev = nullptr;
	CSceneManager*		m_pSceneManager = nullptr;
	CGameObjectManager* m_pGameObjectManager = nullptr;
	CComponentManager*  m_pComponentManager = nullptr;
	CTime_Manager*		m_pTimeManager = nullptr;
	CRenderer*			m_pRenderer = nullptr;

	_uint m_iUpdateEvent = 0;
};
END

#define __MANAGEMENT_H__
#endif
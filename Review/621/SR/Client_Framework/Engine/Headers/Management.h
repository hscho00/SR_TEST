#pragma once
#ifndef __MANAGEMENT_H__
#define __MANAGEMENT_H__

#include "Base.h"
#include "GraphicDevice.h"
#include "SceneManager.h"
#include "GameObjectManager.h"
#include "ComponentManager.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "Renderer.h"

CODEBEGIN(Engine)
class ENGINE_DLL Management final:
    public CBase
{
		DECLARE_SINGLETON(Management)

private:
	Management();
	virtual ~Management() = default;

public:
	/* For.General */
	HRESULT ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, DisplayMode eDisplaymode, _uint iSceneCount);
	_uint UpdateEngine();
	_uint LateUpdateEngine();
	_uint RenderEngine(HWND hWnd = nullptr);
	HRESULT ClearForScene(_int iSceneIndex);

public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 GetDevice();

public:
	const float Get_DeltaTime() { return m_pTimeManager->Get_DeltaTime(); }

public:
	/* For.SceneManager */
	HRESULT SetUpCurrentScene(_int iSceneID, Scene * pCurrentScene);

public:
	/* For.GameObjectManager */
	HRESULT AddGameObjectPrototype(_int iSceneIndex, const wstring & GameObjectTag, GameObject * pPrototype);
	HRESULT AddGameObjectInLayer(_int iFromSceneIndex, const wstring & GameObjectTag, _int iToSceneIndex, const wstring & LayerTag, void* pArg = nullptr);

public:
	/* For.ComponentManager */
	HRESULT AddComponentPrototype(_int iSceneIndex, const wstring & ComponentTag, Component * pPrototype);
	Component* CloneComponentPrototype(_int iSceneIndex, const wstring & ComponentTag, void* pArg = nullptr);

public: /* For.Renderer */
	HRESULT AddGameObjectInRenderer(RenderID eID, class GameObject* pGameObject);

public:
	virtual void Free() override;
	static void ReleaseEngine();

private:
	GraphicDevice* m_pGraphic_Dev = nullptr;
	TimeManager* m_pTimeManager = nullptr;
	SceneManager* m_pSceneManager = nullptr;
	GameObjectManager* m_pGameObjectManager = nullptr;
	ComponentManager* m_pComponentManager = nullptr;
	Renderer* m_pRenderer = nullptr;
	KeyManager* m_pKeyManager = nullptr;
	DOUBLE fDeltaTime = 0;
	_uint m_iUpdateEvent = 0;
};

	CODEEND
#endif
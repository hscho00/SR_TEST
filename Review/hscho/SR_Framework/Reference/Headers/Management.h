#pragma once
#ifndef __MANAGEMENT_H__

#include "Base.h"
#include "Grahpic_Device.h"
#include "SceneManager.h"

////////////////////////////
#include "Vertices.h"
////////////////////////////

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

	////////////////////////////
	std::vector<CVertices*>& Get_VecVertices() { return m_vecVertices; }
	////////////////////////////

public:
	/* For.GraphicDev */
	LPDIRECT3DDEVICE9 GetDevice();

public:
	/* For.SceneManager */
	HRESULT SetUpCurrentScene(_int iSceneID, CScene* pCurrentScene);

public:
	/* For.Renderer */

public:
	virtual void Free() override;
	static void ReleaseEngine();

private:
	CGraphic_Device* m_pGraphic_Dev;
	CSceneManager* m_pSceneManager;

	_uint m_iUpdateEvent;

	////////////////////////////
	std::vector<CVertices*> m_vecVertices;
	////////////////////////////
};
END

#define __MANAGEMENT_H__
#endif
#pragma once
#ifndef __SCENE_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CScene abstract : public CBase
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CScene() = default;

public:
	virtual HRESULT ReadyScene() PURE;
	virtual _uint UpdateScene() PURE;
	virtual _uint LateUpdateScene() PURE;

public:
	_int Get_SceneIndex() const { return m_iSceneIndex; }

public:
	virtual void Free() override PURE;

protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	class CTimeManager* m_pTimeManager;
	class CGameObjectManager* m_pGameObjectManager;

	_int m_iSceneIndex;	// 생성 시 꼭 초기화 필요함

};
END

#define __SCENE_H__
#endif
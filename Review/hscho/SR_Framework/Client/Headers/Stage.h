#pragma once
#ifndef __STAGE_H__

#include "Scene.h"

USING(Engine)
class CStage : public CScene
{
private:
	explicit CStage(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CStage() = default;

public:
	virtual HRESULT ReadyScene() override;
	virtual _uint UpdateScene() override;
	virtual _uint LateUpdateScene() override;

private:
	HRESULT AddPlayerAndLayer();
	HRESULT AddTerrainAndLayer();

public:
	static CStage* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

private:
	CGameObject* m_pPlayer;

	/////////////////////
	// 카메라 생기면 들어낼것들
	_vec3 m_vCameraPos;
	_vec3 m_vTargetPos;
	const _vec3 m_vUpVec;
	_float m_fCameraAngle;
	/////////////////////

};

#define __STAGE_H__
#endif
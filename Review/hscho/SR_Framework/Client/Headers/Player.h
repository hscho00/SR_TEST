#pragma once
#ifndef __PLAYER_H__

#include "GameObject.h"

USING(Engine)
class CPlayer final : public CGameObject
{
public:
	explicit CPlayer(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT ReadyGameObjectPrototype() override;
	virtual HRESULT ReadyGameObject(void* pArg = nullptr) override;
	virtual _uint UpdateGameObject(float fDeltaTime) override;
	virtual _uint LateUpdateGameObject(float fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;
	
public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	//CManagement* m_pManagement;	// Player Free 호출 전에 매니지먼트를 먼저 지움...
	float m_fAngle;

};

#define __PLAYER_H__
#endif
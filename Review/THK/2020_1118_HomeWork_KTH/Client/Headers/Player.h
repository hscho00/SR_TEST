#pragma once
#ifndef __PLAYER_H__

#include "GameObject.h"

USING(Engine)
class CPlayer final : public CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT ReadyGameObjectPrototype() override;
	virtual HRESULT ReadyGameObject(void * pArg = nullptr) override;
	virtual _uint UpdateGameObject(float fDeltaTime) override;
	virtual _uint LateUpdateGameObject(float fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;

protected:
	HRESULT AddComponent();

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;
	virtual CGameObject * Clone(void * pArg = nullptr) override;


private:
	class CVIBuffer* m_pVIBufferCom = nullptr;

};

#define __PLAYER_H__
#endif
#pragma once
#ifndef __PLAYER_H__

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


public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;
	virtual CGameObject * Clone(void * pArg = nullptr) override;

};

#define __PLAYER_H__
#endif
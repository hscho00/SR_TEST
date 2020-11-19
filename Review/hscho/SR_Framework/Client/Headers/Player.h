#pragma once
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
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	float m_fAngle;

};


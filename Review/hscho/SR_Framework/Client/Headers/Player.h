#pragma once
#ifndef __PLAYER_H__

#include "GameObject.h"

USING(Engine)
class CPlayer final : public CGameObject
{
public:
	explicit CPlayer(LPDIRECT3DDEVICE9 pDevice);
	explicit CPlayer(const CPlayer& other);
	virtual ~CPlayer() = default;

public:
	virtual HRESULT ReadyGameObjectPrototype() override;
	virtual HRESULT ReadyGameObject(void* pArg = nullptr) override;
	virtual _uint UpdateGameObject(_float fDeltaTime) override;
	virtual _uint LateUpdateGameObject(_float fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;

private:
	HRESULT AddComponent();

public:
	static CPlayer* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	class CVIBuffer* m_pVIBufferCom;

	//CManagement* m_pManagement;	// Player Free ȣ�� ���� �Ŵ�����Ʈ�� ���� ����...

};

#define __PLAYER_H__
#endif
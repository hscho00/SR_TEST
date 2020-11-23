#pragma once
#ifndef __TERRAIN_H__

#include "GameObject.h"

USING(Engine)
class CTerrain final: public CGameObject
{
public:
	explicit CTerrain(LPDIRECT3DDEVICE9 pDevice);
	explicit CTerrain(const CTerrain& other);
	virtual ~CTerrain() = default;

public:
	virtual HRESULT ReadyGameObjectPrototype() override;
	virtual HRESULT ReadyGameObject(void* pArg = nullptr) override;
	virtual _uint UpdateGameObject(float fDeltaTime) override;
	virtual _uint LateUpdateGameObject(float fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;

private:
	HRESULT AddComponent();

public:
	static CTerrain* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	class CVIBuffer* m_pVIBufferCom;

};

#define __TERRAIN_H__
#endif
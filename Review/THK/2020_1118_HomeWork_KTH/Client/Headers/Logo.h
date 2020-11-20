#pragma once
#ifndef __LOGO_H__

#include "Scene.h"

USING(Engine)
class CLogo : public CScene
{
private:
	IDirect3DVertexBuffer9* VB = 0;
	IDirect3DIndexBuffer9*  IB = 0;
	IDirect3DVertexBuffer9*  Triangle = 0;
	D3DXMATRIX	World;
private:
	explicit CLogo(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CLogo() = default;

public:
	virtual HRESULT ReadyScene() override;
	virtual _uint UpdateScene() override;
	virtual _uint LateUpdateScene() override;

public:
	static CLogo* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;


private:
	float m_fX = -2.f;
	float m_fY = 0.f;
	float m_fZ = 0.f;
	float m_fAngle = 0.f;
};

#define __LOGO_H__
#endif

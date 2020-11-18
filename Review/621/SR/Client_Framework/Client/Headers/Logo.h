#pragma once
#ifndef __LOGO_H__
#define __LOGO_H__

#include "Scene.h"

USING(Engine)
class Logo :
    public Scene
{
private:
	explicit Logo(LPDIRECT3DDEVICE9 pDevice);
	virtual ~Logo() = default;

public:
	virtual HRESULT ReadyScene() override;
	virtual _uint UpdateScene() override;
	virtual _uint LateUpdateScene() override;

public:
	static Logo* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

private:
	float m_cube_rotation_y = 0.f;	// 큐브 회전
	float m_cube_rotation_x = 0.f;
	IDirect3DVertexBuffer9* VB = 0;
	IDirect3DIndexBuffer9* IB = 0;
};

#endif
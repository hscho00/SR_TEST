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

public:
	static CStage* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

private:
	IDirect3DVertexBuffer9* VB = 0;
	IDirect3DIndexBuffer9*  IB = 0;

};

#define __STAGE_H__
#endif

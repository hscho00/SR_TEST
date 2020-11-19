#pragma once
#ifndef __SCENE_H__

#include "Base.h"

CODEBEGIN(Engine)
class ENGINE_DLL Scene abstract : public CBase
{
protected:
	explicit Scene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~Scene() = default;

public:
	virtual HRESULT ReadyScene();
	virtual _uint UpdateScene();
	virtual _uint LateUpdateScene();

public:
	virtual void Free() override;

protected:
	LPDIRECT3DDEVICE9	m_pDevice;
};
CODEEND

#define __SCENE_H__
#endif
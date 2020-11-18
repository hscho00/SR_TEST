#pragma once
#include "Scene.h"

USING(Engine)
class Stage :
    public Scene
{
private:
	explicit Stage(LPDIRECT3DDEVICE9 pDevice);
	virtual ~Stage() = default;

public:
	virtual HRESULT ReadyScene() override;
	virtual _uint UpdateScene() override;
	virtual _uint LateUpdateScene() override;

public:
	static Stage* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;
};


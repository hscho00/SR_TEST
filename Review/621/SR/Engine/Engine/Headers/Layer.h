#pragma once
#ifndef __LAYER_H__
#define __LAYER_H__

#include "Base.h"

BEGIN(Engine)
class Layer :
    public CBase
{
private:
    Layer();
    virtual ~Layer() = default;

public:
	HRESULT AddGameObjectInLayer(class GameObject* pGameObject);
	_uint UpdateGameObject(float fDeltaTime);
	_uint LateUpdateGameObject(float fDeltaTime);

public:
	virtual void Free() override;

private:
	typedef list<class GameObject*>	GAMEOBJECTS;
	GAMEOBJECTS	m_GameObjects;	/* ���� ������Ʈ�� Ŭ�е��� ���� */

};
END
#endif
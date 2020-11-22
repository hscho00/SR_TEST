#pragma once
#ifndef __LAYER_H__
#define __LAYER_H__

#include "Base.h"

CODEBEGIN(Engine)
class Layer :
    public CBase
{
private:
    Layer();
    virtual ~Layer() = default;

public:
	static Layer* Create();
	virtual void	Free() override;

public:
	HRESULT AddGameObjectInLayer(class GameObject* pGameObject);
	_uint UpdateGameObject(DOUBLE fDeltaTime);
	_uint LateUpdateGameObject(DOUBLE fDeltaTime);

private:
	typedef list<class GameObject*>	GAMEOBJECTS;
	GAMEOBJECTS	m_GameObjects;	/* ���� ������Ʈ�� Ŭ�е��� ���� */

};
CODEEND
#endif
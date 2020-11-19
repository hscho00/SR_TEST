#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL GameObject abstract : public CBase
{
protected:
	explicit	GameObject(_lpd3dd9 _pDevice);
	virtual		~GameObject() = default;

public:
	virtual HRESULT ReadyGameObjectPrototype() = 0;	/* 프로토타입 초기화 */
	virtual HRESULT ReadyGameObject(void* _pArg = nullptr) = 0; /* 클론 초기화 */
	virtual _uint UpdateGameObject(float _fDeltaTime) = 0;
	virtual _uint LateUpdateGameObject(float _fDeltaTime) = 0;
	virtual HRESULT RenderGameObject() = 0;

public:
	virtual GameObject* Clone(void* _pArg = nullptr) = 0;
	virtual void Free() override;

protected:
	_lpd3dd9 m_pDevice;

	unordered_map<wstring, class Component*> m_pComponents;
};
END
#endif
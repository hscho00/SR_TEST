#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Base.h"
#include "Vertices.h"

CODEBEGIN(Engine)
class ENGINE_DLL GameObject abstract : public CBase
{
protected:
	explicit	GameObject(_lpd3dd9 _pDevice);
	virtual		~GameObject() = default;

public:
	virtual HRESULT ReadyGameObjectPrototype() = 0;	/* ������Ÿ�� �ʱ�ȭ */
	virtual HRESULT ReadyGameObject(void* _pArg = nullptr) = 0; /* Ŭ�� �ʱ�ȭ */
	virtual _uint UpdateGameObject(DOUBLE _fDeltaTime) = 0;
	virtual _uint LateUpdateGameObject(DOUBLE _fDeltaTime) = 0;
	virtual HRESULT RenderGameObject() = 0;

public:
	virtual GameObject* Clone(void* _pArg = nullptr) = 0;
	virtual void Free() override;

protected:
	_lpd3dd9 m_pDevice;

	typedef	unordered_map<wstring, class Component*> COMPONENTS;
	COMPONENTS m_pComponents;

	// ������Ʈ �ʿ�
	_vector3 m_vPos;
	Vertices* m_pVertices;
	_matrix m_matWorld;
};
CODEEND
#endif
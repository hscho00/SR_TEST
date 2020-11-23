#pragma once
#ifndef __GAMEOBJECT_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pDevice);
	explicit CGameObject(const CGameObject& other);
	virtual ~CGameObject() = default;

public:
	virtual HRESULT ReadyGameObjectPrototype() PURE;	/* ������Ÿ�� �ʱ�ȭ */
	virtual HRESULT ReadyGameObject(void* pArg = nullptr) PURE; /* Ŭ�� �ʱ�ȭ */
	virtual _uint UpdateGameObject(float fDeltaTime) PURE;
	virtual _uint LateUpdateGameObject(float fDeltaTime) PURE;
	virtual HRESULT RenderGameObject() PURE;

public:
	_bool IsUsing() const { return m_bUsing; }
	void Set_Using(_bool bUsing) { m_bUsing = bUsing; }

	_bool IsDead() const { return m_bDead; }
	void Set_Dead(_bool bDead) { m_bDead = bDead; }

	_bool IsDraw() const { return m_bDraw; }
	void Set_Draw(_bool bDraw) { m_bDraw = bDraw; }

	/////////////////////////////////////
	const _vec3& Get_Pos() const { return m_vPos; }
	/////////////////////////////////////

protected:
	HRESULT AddComponent(_int iSceneIndex, const wstring& PrototypeTag, const wstring& ComponentTag, class CComponent** ppComponent = nullptr, void* pArg = nullptr);

public:
	// static CGameObject* Create(LPDIRECT3DDEVICE9 pDevice) �� ������ 
	virtual CGameObject* Clone(void* pArg = nullptr) PURE;
	virtual void Free() override PURE;
	
protected:
	LPDIRECT3DDEVICE9	m_pDevice;

	typedef unordered_map<wstring, class CComponent*> COMPONENTS;
	COMPONENTS	m_Components;

	_bool m_bUsing;	// false�� update �� �ٷ� ���� ����
	_bool m_bDead;	// true�� �ʱ�ȭ �� using false ó��
	_bool m_bDraw;	// false�� render X

	//////////////
	// Transform ������Ʈ�� ����� ��ü�ɰ͵�
	_vec3 m_vPos;
	float m_fAngle;
	_matrix m_matWorld;
	//////////////

};
END

#define __GAMEOBJECT_H__
#endif
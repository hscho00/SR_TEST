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

public:
	virtual HRESULT ReadyGameObjectPrototype() PURE;	/* 프로토타입 초기화 */
	virtual HRESULT ReadyGameObject(void* pArg = nullptr) PURE; /* 클론 초기화 */
	virtual _uint UpdateGameObject(_float fDeltaTime) PURE;
	virtual _uint LateUpdateGameObject(_float fDeltaTime) PURE;
	virtual HRESULT RenderGameObject() PURE;

public:
	_bool IsUsing() const { return m_bUsing; }
	void Set_Using(_bool bUsing) { m_bUsing = bUsing; }

	_bool IsDead() const { return m_bDead; }
	void Set_Dead(_bool bDead) { m_bDead = bDead; }

	_bool IsDraw() const { return m_bDraw; }
	void Set_Draw(_bool bDraw) { m_bDraw = bDraw; }

	class CComponent* GetComponentOrNull(const wstring& ComponentTag);

	/////////////////////////////////////
	const _vec3& Get_Pos() const { return m_vPos; }
	/////////////////////////////////////

protected:
	HRESULT AddComponent(_int iSceneIndex, const wstring& PrototypeTag, const wstring& ComponentTag, class CComponent** ppComponent = nullptr, void* pArg = nullptr);

public:
	// static CGameObject* Create(LPDIRECT3DDEVICE9 pDevice) 도 만들자 
	virtual CGameObject* Clone(void* pArg = nullptr) PURE;
	virtual void Free() override PURE;
	
protected:
	LPDIRECT3DDEVICE9	m_pDevice;

	typedef unordered_map<wstring, class CComponent*> COMPONENTS;
	COMPONENTS	m_Components;

	_bool m_bUsing;	// false면 update 시 바로 빠져 나감
	_bool m_bDead;	// true면 초기화 후 using false 처리
	_bool m_bDraw;	// false면 render X

	//////////////
	// Transform 컴포넌트가 생기면 대체될것들
	_vec3 m_vPos;
	_float m_fAngle;
	_matrix m_matWorld;
	//////////////

};
END

#define __GAMEOBJECT_H__
#endif
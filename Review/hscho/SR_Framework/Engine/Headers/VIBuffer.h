#pragma once
#ifndef __VIBUFFER_H__

#include "Component.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer(const CVIBuffer& other);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT ReadyComponentPrototype() PURE;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) PURE;
	virtual HRESULT Render_VIBuffer() PURE;

public:
	virtual CComponent* Clone(void* pArg = nullptr) PURE;
	virtual void Free() override;

protected:
	/*
	버텍스버퍼 컴객체: 여러 버텍스들을 배열 형식으로 보관하고 관리하는 컴객체.
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	_uint m_iVertexSize;
	_uint m_iVertexCount;
	_uint m_iTriCount;
	_uint m_iFVF; /* Flexible Vertex Format */

	/*
	인덱스버퍼 컴객체 : 여러 인덱스들을 배열 형식으로 보관하고 관리하는 컴객체.
	인덱스 : 하나의 폴리곤을 구성하는 정점들의 이웃관계를 표현하는 도구.
	*/
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	_uint		m_iIndexSize;
	D3DFORMAT	m_IndexFormat;

};
END

#define __VIBUFFER_H__
#endif


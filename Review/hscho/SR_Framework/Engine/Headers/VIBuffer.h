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
	���ؽ����� �İ�ü: ���� ���ؽ����� �迭 �������� �����ϰ� �����ϴ� �İ�ü.
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	_uint m_iVertexSize;
	_uint m_iVertexCount;
	_uint m_iTriCount;
	_uint m_iFVF; /* Flexible Vertex Format */

	/*
	�ε������� �İ�ü : ���� �ε������� �迭 �������� �����ϰ� �����ϴ� �İ�ü.
	�ε��� : �ϳ��� �������� �����ϴ� �������� �̿����踦 ǥ���ϴ� ����.
	*/
	LPDIRECT3DINDEXBUFFER9 m_pIB;
	_uint		m_iIndexSize;
	D3DFORMAT	m_IndexFormat;

};
END

#define __VIBUFFER_H__
#endif


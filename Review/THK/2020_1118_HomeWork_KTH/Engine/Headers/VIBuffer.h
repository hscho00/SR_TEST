#pragma once
#ifndef __VIBUFFER_H__
#include "Component.h"


BEGIN(Engine)
class ENGINE_DLL CVIBuffer abstract : public CComponent
{
public:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT ReadyComponentPrototype() = 0;
	virtual HRESULT ReadyComponent(void * pArg = nullptr) = 0;
	virtual HRESULT Render_VIBuffer() = 0;

public:
	virtual CComponent * Clone(void * pArg = nullptr) = 0;
	virtual void Free() override;

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVB = nullptr;
	_uint m_iVertexSize = 0;
	_uint m_iVertexCount = 0;
	_uint m_iTriCount = 0;
	_uint m_iFVF = 0;



};


END
#define  __VIBUFFER_H__
#endif
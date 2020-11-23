#pragma once
#ifndef __VIBUFFER_QUADCOLOR_H__

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_QuadColor final : public CVIBuffer
{
protected:
	explicit CVIBuffer_QuadColor(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer_QuadColor(const CVIBuffer_QuadColor& other);
	virtual ~CVIBuffer_QuadColor() = default;

public:
	virtual HRESULT ReadyComponentPrototype() override;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
	virtual HRESULT Render_VIBuffer() override;

public:
	static CVIBuffer_QuadColor* Create(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color);
	virtual CComponent* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	_uint m_iColor;

};
END

#define __VIBUFFER_QUADCOLOR_H__
#endif


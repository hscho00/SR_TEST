#pragma once
#ifndef __VIBUFFER_TRUCOLOR_H__
#define __VIBUFFER_TRUCOLOR_H__

#include "VIBuffer.h"

CODEBEGIN(Engine)
class ENGINE_DLL VIBuffer_TriColor final :
    public VIBuffer
{
private:
	explicit VIBuffer_TriColor(_lpd3dd9 pDevice);
	explicit VIBuffer_TriColor(const VIBuffer_TriColor& other);
	virtual ~VIBuffer_TriColor() = default;

public:
	virtual HRESULT ReadyComponentPrototype() override;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
	virtual HRESULT Render_VIBuffer() override;

public:
	static VIBuffer_TriColor* Create(_lpd3dd9 pDevice);
	virtual Component* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	_uint m_iColor;
};
CODEEND

#endif
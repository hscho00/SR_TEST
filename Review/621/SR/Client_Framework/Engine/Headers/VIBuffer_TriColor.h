#pragma once
#ifndef __VIBUFFER_TRUCOLOR_H__
#define __VIBUFFER_TRUCOLOR_H__

#include "VIBuffer.h"

CODEBEGIN(Engine)
class ENGINE_DLL VIBuffer_TriColor final :
    public VIBuffer
{
private:
	explicit VIBuffer_TriColor(LPDIRECT3DDEVICE9 pDevice);
	virtual ~VIBuffer_TriColor() = default;

public:
	virtual HRESULT ReadyComponentPrototype() override;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
	virtual HRESULT Render_VIBuffer() override;

public:
	static VIBuffer_TriColor* Create(
		_lpd3dd9 pDevice,
		VTX_COLOR vertices[],
		_uint verticesCount,
		WORD indices[],
		_uint indicesCount,
		_uint primCount
	);
	virtual Component* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	HRESULT ReadyVertices(
		VTX_COLOR vertices[],
		_uint verticesCount,
		WORD indices[],
		_uint indicesCount,
		_uint primCount);
};
CODEEND

#endif
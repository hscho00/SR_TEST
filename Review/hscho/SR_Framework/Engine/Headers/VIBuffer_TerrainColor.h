#pragma once
#ifndef __VIBUFFER_TERRAINCOLOR_H__

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_TerrainColor final : public CVIBuffer
{
protected:
	explicit CVIBuffer_TerrainColor(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color,
									_uint iVertexCountX, _uint iVertexCountZ, _float fVertexInterval);
	explicit CVIBuffer_TerrainColor(const CVIBuffer_TerrainColor& other);
	virtual ~CVIBuffer_TerrainColor() = default;

public:
	virtual HRESULT ReadyComponentPrototype() override;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
	virtual HRESULT Render_VIBuffer() override;

public:
	static CVIBuffer_TerrainColor* Create(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color,
										_uint iVertexCountX, _uint iVertexCountZ, _float fVertexInterval = 1.f);
	virtual CComponent* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	_uint m_iColor;
	_uint m_iVertexCountX;
	_uint m_iVertexCountZ;
	_float m_fVertexInterval;

};
END

#define __VIBUFFER_TERRAINCOLOR_H__
#endif

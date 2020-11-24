#pragma once
#ifndef __VIBUFFER_TERRAINCOLOR_H__

#include "VIBuffer.h"

BEGIN(Engine)
class ENGINE_DLL CVIBuffer_TerrainColor final : public CVIBuffer
{
protected:
	explicit CVIBuffer_TerrainColor(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer_TerrainColor(const CVIBuffer_TerrainColor& other);
	virtual ~CVIBuffer_TerrainColor() = default;

public:
	virtual HRESULT ReadyComponentPrototype() override;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
	virtual HRESULT Render_VIBuffer() override;

public:
	static CVIBuffer_TerrainColor* Create(LPDIRECT3DDEVICE9 pDevice, _uint iCX, _uint iCY, D3DCOLOR color);
	virtual CComponent* Clone(void* pArg = nullptr) override;
	virtual void Free() override;

private:
	_uint m_iCX;
	_uint m_iCY;
	_uint m_iColor;

};
END

#define __VIBUFFER_TERRAINCOLOR_H__
#endif

#pragma once
#ifndef __VIBUFFER_TERRAINCOLOR_H__
#define __VIBUFFER_TERRAINCOLOR_H__

#include "VIBuffer.h"

CODEBEGIN(Engine)
class ENGINE_DLL VIBuffer_TerrainColor :
    public VIBuffer
{
private:
    explicit VIBuffer_TerrainColor(_lpd3dd9 pDevice);
    explicit VIBuffer_TerrainColor(const VIBuffer_TerrainColor& other);
    virtual ~VIBuffer_TerrainColor() = default;

public:
    static VIBuffer_TerrainColor* Create(LPDIRECT3DDEVICE9 pDevice, _uint _terrain_x = 4, _uint _terrain_y = 4, _float _VertexIntervel = 1.f);
    virtual Component* Clone(void* pArg = nullptr) override;
    virtual void Free() override;

public:
    virtual HRESULT ReadyComponentPrototype() override;
    virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
    virtual HRESULT Render_VIBuffer() override;

public:
    int CalaulateVerticesIndex();
    void SetSize(_uint _terrain_x = 4, _uint _terrain_y = 4, _float _VertexIntervel = 1.f);
private:
    _uint   Terrain_x = 4;
    _uint   Terrain_y = 4;
    _float  m_VertexIntervel = 1.f;

};
CODEEND
#endif


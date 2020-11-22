#pragma once
#ifndef __VERTICES_H__
#define __VERTICES_H__

#include "Component.h"

CODEBEGIN(Engine)
class ENGINE_DLL Vertices final : public Component
{
public:
    explicit Vertices(_lpd3dd9 pDevice);
    virtual ~Vertices() = default;

public:
    static Vertices* Create(
        _lpd3dd9 pDevice,
        Vertex vertices[],
        _uint verticesCount,
        WORD indices[],
        _uint indicesCount,
        _uint primCount);
    virtual Component* Clone(void* pArg = nullptr) override;
    virtual void Free() override;

public:
    virtual HRESULT ReadyComponentPrototype() override;
    virtual HRESULT ReadyComponent(void* pArg = nullptr) override;



private:
    HRESULT ReadyVertices(
        Vertex vertices[],
        _uint verticesCount,
        WORD indices[],
        _uint indicesCount,
        _uint primCount);

private:
    IDirect3DVertexBuffer9* m_pVertexBuffer;
    IDirect3DIndexBuffer9*  m_pIndexBuffer;
    _uint                   m_iVerticesCount;
    _uint                   m_iPrimCount;
};

CODEEND
#endif

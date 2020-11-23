#pragma once
#ifndef __VIBUFFER_H__
#define __VIBUFFER_H__

#include "Component.h"

CODEBEGIN(Engine)
class ENGINE_DLL VIBuffer abstract : public Component
{
protected:
    explicit VIBuffer(_lpd3dd9 pDevice);
    explicit VIBuffer(const VIBuffer& other);
    virtual ~VIBuffer() = default;

public:
    virtual Component* Clone(void* pArg = nullptr) = 0;
    virtual void Free() override;

public:
    virtual HRESULT ReadyComponentPrototype() override;
    virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
    virtual HRESULT Render_VIBuffer() = 0;

protected:
    IDirect3DVertexBuffer9* m_pVertexBuffer;    
    IDirect3DIndexBuffer9*  m_pIndexBuffer;
    _uint                   m_iVerticesCount;   // vertex °³¼ö
    _uint                   m_iVerticesSize = 0;
    _uint                   m_iIndexSize = 0;
    _uint                   m_iPrimCount;   //
    _uint                   m_iFVF = 0;
};

CODEEND
#endif

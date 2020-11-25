#pragma once
#ifndef __VIBUFFER_RECTCOLOR_H__
#define __VIBUFFER_RECTCOLOR_H__

#include "VIBuffer.h"

CODEBEGIN(Engine)
class ENGINE_DLL VIBuffer_RectColor final :
    public VIBuffer
{
private:
    explicit VIBuffer_RectColor(_lpd3dd9 pDevice);
    explicit VIBuffer_RectColor(const VIBuffer_RectColor& other);
    virtual ~VIBuffer_RectColor() = default;

public:
    static VIBuffer_RectColor* Create(LPDIRECT3DDEVICE9 pDevice);
    virtual Component* Clone(void* pArg = nullptr) override;
    virtual void Free() override;

public:
    virtual HRESULT ReadyComponentPrototype() override;
    virtual HRESULT ReadyComponent(void* pArg = nullptr) override;
    virtual HRESULT Render_VIBuffer() override;
};

CODEEND

#endif


#pragma once
#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "Base.h"

CODEBEGIN(Engine)
class ENGINE_DLL Component :
    public CBase
{
public:
    explicit Component(_lpd3dd9 pDevice);
    virtual ~Component() = default;

public:
    virtual HRESULT ReadyComponentPrototype() = 0;
    virtual HRESULT ReadyComponent(void* pArg = nullptr) = 0;

public:
    virtual Component* Clone(void* pArg = nullptr) = 0;
    virtual void Free() override;

protected:
    _lpd3dd9    m_pDevice;
};
CODEEND
#endif

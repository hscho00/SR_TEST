#pragma once
#ifndef __COMPONENT_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CComponent abstract : public CBase
{
public:
	explicit CComponent(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CComponent() = default;

public:
	virtual HRESULT ReadyComponentPrototype() PURE;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) PURE;

public:
	virtual CComponent* Clone(void* pArg = nullptr) PURE;
	virtual void Free() override;

protected:
	LPDIRECT3DDEVICE9	m_pDevice;
};
END

#define __COMPONENT_H__
#endif
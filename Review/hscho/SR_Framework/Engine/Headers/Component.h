#pragma once
#ifndef __COMPONENT_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CComponent abstract : public CBase
{
public:
	explicit CComponent(LPDIRECT3DDEVICE9 pDevice);
	explicit CComponent(const CComponent& other);
	virtual ~CComponent() = default;

public:
	virtual HRESULT ReadyComponentPrototype() PURE;
	virtual HRESULT ReadyComponent(void* pArg = nullptr) PURE;

public:	
	// static CComponent* Create(LPDIRECT3DDEVICE9 pDevice) 도 만들자 
	virtual CComponent* Clone(void* pArg = nullptr) PURE;
	virtual void Free() override;

protected:
	LPDIRECT3DDEVICE9	m_pDevice;
};
END

#define __COMPONENT_H__
#endif
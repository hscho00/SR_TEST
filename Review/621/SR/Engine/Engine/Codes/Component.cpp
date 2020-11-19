#include "..\Headers\Component.h"

USING(Engine)
Component::Component(_lpd3dd9 pDevice)
	:m_pDevice(pDevice)
{
	SafeAddRef(m_pDevice);
}

HRESULT Component::ReadyComponentPrototype()
{
	return S_OK;
}

HRESULT Component::ReadyComponent(void* pArg)
{
	return S_OK;
}

void Component::Free()
{
	SafeRelease(m_pDevice);
}

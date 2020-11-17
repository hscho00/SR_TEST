#pragma once
#ifndef __GRAPHIC_DEVICE_H__

#include "Base.h"

class ENGINE_DLL CGraphic_Device final : public CBase
{
	DECLARE_SINGLETON(CGraphic_Device)

private:
	CGraphic_Device();
	virtual ~CGraphic_Device() = default;

public:
	LPDIRECT3DDEVICE9 Get_Device() const { return m_pDevice; }

	HRESULT Ready_Graphic_Device(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplayMode);

	void Render_Begin();
	void Render_End(HWND hWND = nullptr);

public:
	virtual void Free() override;

private:
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;

};

#define __GRAPHIC_DEVICE_H__
#endif
#pragma once
#ifndef __GRAPHIC_DEVICE_H__
#define __GRAPHIC_DEVICE_H__

#include "Base.h"

BEGIN(Engine)
class GraphicDevice final :
    public CBase
{
    DECLARE_SINGLETON(GraphicDevice)

private:
	GraphicDevice();
	virtual ~GraphicDevice() = default;

public:
	LPDIRECT3DDEVICE9 Get_Device_() { return Device_; }
	
public:
	HRESULT ReadyGraphicDevice(HWND hWnd, _uint iWinCX, _uint iWinCY, DisplayMode eDisplayMode);
	void RenderBegin();
	void RenderEnd(HWND hWnd = nullptr);

public:
	virtual void Free() override;

private:
	LPDIRECT3D9 Sdk_; // �׷���ī���� ������ �����ϰ� �����ϴ� ��ü. 
	LPDIRECT3DDEVICE9 Device_; // �ְ� ���������� �׷��� ��ġ�� �����ϴ� ��ü. 
};
END
#endif


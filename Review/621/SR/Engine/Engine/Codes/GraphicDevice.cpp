#include "GraphicDevice.h"

USING(Engine)

IMPLEMENT_SINGLETON(GraphicDevice)

GraphicDevice::GraphicDevice()
	: Sdk_(nullptr)
	, Device_(nullptr)
{
}

HRESULT GraphicDevice::ReadyGraphicDevice(HWND hWnd, _uint iWinCX, _uint iWinCY, DisplayMode eDisplayMode)
{
	D3DCAPS9 DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));

	Sdk_ = Direct3DCreate9(D3D_SDK_VERSION);

	if (FAILED(Sdk_->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		LOG_MSG(L"Error", L"Device Caps Load Failed");
		return E_FAIL;
	}

	DWORD vp = 0;
	if (DeviceCaps.DevCaps & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = iWinCX;
	d3dpp.BackBufferHeight = iWinCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = (BOOL)eDisplayMode;// TRUE일 경우 창모드, FALSE 전체화면. 
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED(Sdk_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, vp, &d3dpp, &Device_)))
	{
		LOG_MSG(L"Error", L"GraphicDevice Creating Failed");
		return E_FAIL;
	}

	return S_OK;
}


void GraphicDevice::RenderBegin()
{
	Device_->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	Device_->BeginScene();
}

void GraphicDevice::RenderEnd(HWND hWnd)
{
	Device_->EndScene();
	Device_->Present(nullptr, nullptr, hWnd, nullptr);
}

void GraphicDevice::Free()
{
	if (SafeRelease(Device_))
	{
		LOG_MSG(L"Error", L"Device release failed.");
	}

	if (SafeRelease(Sdk_))
	{
		LOG_MSG(L"Error", L"SDK release failed.");
	}
}

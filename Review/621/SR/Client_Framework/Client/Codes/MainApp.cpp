#include "stdafx.h"
#include "MainApp.h"
#include "GraphicDevice.h"

MainApp::MainApp()
{
}

HRESULT MainApp::ReadyMainApp()
{
	if (FAILED(GraphicDevice::Get_Instance()->ReadyGraphicDevice(g_hWnd, WINCX, WINCY, DisplayMode::WINDOW)))
	{
		LOG_MSG(L"Error", L"Preparation of Graphic_Device has Failed");
		return E_FAIL;
	}
	return S_OK;
}

int MainApp::UpdateMainApp()
{
	GraphicDevice::Get_Instance()->RenderBegin();
	GraphicDevice::Get_Instance()->RenderEnd();
	return 0;
}

MainApp* MainApp::Create()
{
	MainApp* pInstance = new MainApp;
	if (FAILED(pInstance->ReadyMainApp()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

void MainApp::Free()
{
}

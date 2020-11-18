#include "stdafx.h"
#include "MainApp.h"
#include "GraphicDevice.h"

MainApp::MainApp()
	: m_pGraphic_device(GraphicDevice::Get_Instance())
{
}

HRESULT MainApp::ReadyMainApp()
{
	if (FAILED(m_pGraphic_device->ReadyGraphicDevice(g_hWnd, WINCX, WINCY, DisplayMode::WINDOW)))
	{
		LOG_MSG(L"Error", L"Preparation of Graphic_Device has Failed");
		return E_FAIL;
	}
	return S_OK;
}

int MainApp::UpdateMainApp()
{
	m_pGraphic_device->RenderBegin();
	m_pGraphic_device->RenderEnd();
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
	m_pGraphic_device->Free();
}

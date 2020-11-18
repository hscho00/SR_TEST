#include "stdafx.h"
#include "MainApp.h"

MainApp::MainApp()
	: m_pManagement(Management::Get_Instance())
{
	SafeAddRef(m_pManagement);
}

HRESULT MainApp::ReadyMainApp()
{
	if (FAILED(m_pManagement->ReadyEngine(g_hWnd, WINCX, WINCY, DisplayMode::WINDOW)))
	{
		LOG_MSG(L"Error", L"Preparation of Graphic_Device has Failed");
		return E_FAIL;
	}
	return S_OK;
}

int MainApp::UpdateMainApp()
{

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

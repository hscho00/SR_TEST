#include "stdafx.h"
#include "MainApp.h"
#include "Logo.h"
MainApp::MainApp()
	: m_pManagement(Management::Get_Instance())
{
	SafeAddRef(m_pManagement);
}

HRESULT MainApp::ReadyMainApp()
{
	if (FAILED(m_pManagement->ReadyEngine(g_hWnd, WINCX, WINCY,
		DisplayMode::WINDOW)))
	{
		LOG_MSG(L"Error", L"Preparation of Graphic_Device has Failed");
		return E_FAIL;
	}

		if (FAILED(m_pManagement->SetUpCurrentScene((_int)SceneID::Logo,
		Logo::Create(m_pManagement->GetDevice()))))
	{
		LOG_MSG(L"Error", L"Failed To SetUpCurrentScene");
		return E_FAIL;
	}
	return S_OK;
}

int MainApp::UpdateMainApp()
{
	m_pManagement->UpdateEngine();

	return 0;
}

MainApp* MainApp::Create()
{
	MainApp* pInstance = new MainApp;
	if (FAILED(pInstance->ReadyMainApp()))
	{
		LOG_MSG(L"Error", L"Failed To Create MainApp");
		SafeRelease(pInstance);
	}
	return pInstance;
}

void MainApp::Free()
{
	SafeRelease(m_pManagement);
	Management::ReleaseEngine();
}

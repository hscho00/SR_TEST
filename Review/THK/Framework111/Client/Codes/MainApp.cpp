#include "stdafx.h"
#include "MainApp.h"
#include "Graphic_Device.h"
CMainApp::CMainApp()
	:m_pGraphic_Device(CGraphic_Device::Get_Instance())
{
}

HRESULT CMainApp::ReadyMainApp()
{
	m_pGraphic_Device->Ready_Graphic_Device(g_hWnd, WINCX, WINCY, EDisplayMode::Window);
	return S_OK;
}

int CMainApp::UpdateMainApp()
{
	m_pGraphic_Device->Render_Begin();
	m_pGraphic_Device->Render_End();
	return 0;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->ReadyMainApp()))
	{
		//log
		//messagebox

		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CMainApp::Free()
{
}

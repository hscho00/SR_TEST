#include "stdafx.h"
#include "MainApp.h"


CMainApp::CMainApp()
	: m_pGraphicDevice(CGraphic_Device::Get_Instance())
{

}

HRESULT CMainApp::ReadyMainApp()
{
	m_pGraphicDevice->Ready_Graphic_Device(g_hWnd, WINCX, WINCY, EDisplayMode::Windowed);

	return S_OK;
}

int CMainApp::UpdateMainApp()
{
	m_pGraphicDevice->Render_Begin();
	
	m_pGraphicDevice->Render_End();

	return 0;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;

	if (FAILED(pInstance->ReadyMainApp()))
	{
		//log
		//messagebox

		//SafeDelete(pInstance);
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void CMainApp::Free()
{

}
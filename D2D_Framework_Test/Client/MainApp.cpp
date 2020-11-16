#include "stdafx.h"
#include "MainApp.h"
#include "Graphic_Device.h"
#include "Texture_Manager.h"
#include "TimeManager.h"
#include "FrameManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "ObjManager.h"
#include "ScrollManager.h"

CMainApp::CMainApp()
	: m_pGraphic_Device(CGraphic_Device::Get_Instance())
	, m_pTimeManager(CTimeManager::Get_Instance())
	, m_pKeyManager(CKeyManager::Get_Instance())
	, m_pSceneManager(CSceneManager::Get_Instance())
	, m_pObjManager(CObjManager::Get_Instance())
{

}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		return nullptr;
	}
	return pInstance;
}

void CMainApp::Destroy()
{
	Release_MainApp();
}

HRESULT CMainApp::Ready_MainApp()
{
	srand((unsigned int)time(NULL));

	if (FAILED(m_pGraphic_Device->Ready_Graphic_Device(CGraphic_Device::MODE_WINDONED)))
	{
		ERR_MSG(L"Ready Graphic_Device Failed");
		return E_FAIL;
	}

	if (FAILED(m_pTimeManager->Ready_TimeMgr()))
		return E_FAIL;

	if (FAILED(m_pSceneManager->ChangeScene(SCENE::ID::STAGE_1)))
		return E_FAIL;

	return S_OK; 
}

void CMainApp::Update_MainApp()
{
	m_pTimeManager->Compute_TimeMgr();
	m_pKeyManager->Update_KeyMgr();
	m_pSceneManager->Update_SceneMgr();

#ifdef _DEBUG
	if (CKeyManager::Get_Instance()->IsKeyPressing(CKeyManager::LSHIFT))
		g_bDebugMode = TRUE;
	else
		g_bDebugMode = FALSE;
#endif
}

void CMainApp::LateUpdate_MainApp()
{
	m_pSceneManager->LateUpdate_SceneMgr();
	CScrollManager::ScrollRock();
}

void CMainApp::Render_MainApp(CFrameManager* pFrameManager)
{
	m_pGraphic_Device->Render_Begin();

	m_pSceneManager->Render_SceneMgr();
	//pFrameManager->RenderFPS();

	m_pGraphic_Device->Render_End();
}

void CMainApp::Release_MainApp()
{
	m_pSceneManager->Destroy_Instance();	// 지우는 순서
	m_pObjManager->Destroy_Instance();		// 지키자 ㅠㅠㅠㅠ
	m_pKeyManager->Destroy_Instance();
	m_pTimeManager->Destroy_Instance();
	CTexture_Manager::Destroy_Instance();
	m_pGraphic_Device->Destroy_Instance();
}
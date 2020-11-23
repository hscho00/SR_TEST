#include "stdafx.h"
#include "MainApp.h"

#include "Logo.h"
#include "Player.h"


CMainApp::CMainApp()
	: m_pManagement(CManagement::Get_Instance())
	, m_pDevice(nullptr)
{
	// 외부에서 가져온 포인터가 누군가 소유한 포인터다,
	// 그 포인터를 자기도 소유한다(멤버변수로), 면 AddRef() 해주자
	SafeAddRef(m_pManagement);
}

HRESULT CMainApp::ReadyMainApp()
{
	//
	if (FAILED(m_pManagement->ReadyEngine(g_hWnd, WINCX, WINCY, EDisplayMode::Windowed, 
										(_int)ESceneID::MaxCount, true, (_int)ESceneID::Static)))
	{
		PRINT_LOG(L"Error", L"Failed To ReadyEngine");
		return E_FAIL;
	}
	
	//
	m_pDevice = m_pManagement->GetDevice();
	if (nullptr == m_pDevice)
		return E_FAIL;
	SafeAddRef(m_pDevice);

	//
	if (FAILED(ReadyStaticResources()))
	{
		PRINT_LOG(L"Error", L"Failed To ReadyStaticResources");
		return E_FAIL;
	}

	//
	if (FAILED(m_pManagement->SetUpCurrentScene(CLogo::Create(m_pManagement->GetDevice()))))
	{
		PRINT_LOG(L"Error", L"Failed To SetUpCurrentScene");
		return E_FAIL;
	}

	return S_OK;
}

_int CMainApp::UpdateMainApp()
{
	m_pManagement->UpdateEngine();
	m_pManagement->RenderEngine();

	return 0;
}

HRESULT CMainApp::ReadyStaticResources()
{
	/* For.GameObject */
#pragma region GameObject_Player
	if (FAILED(m_pManagement->AddGameObjectPrototype((_int)ESceneID::Static,
													L"GameObject_Player",
													CPlayer::Create(m_pDevice))))
	{
		return E_FAIL;
	}
#pragma endregion

	/* For.Component */
#pragma region Component_VIBuffer_TriColor
	if (FAILED(m_pManagement->AddComponentPrototype((_int)ESceneID::Static,
													L"Component_VIBuffer_TriColor",
													CVIBuffer_TriColor::Create(m_pDevice))))
	{
		return E_FAIL;
	}
#pragma endregion

	return S_OK;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->ReadyMainApp()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CMainApp");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pManagement);
	CManagement::ReleaseEngine();
}
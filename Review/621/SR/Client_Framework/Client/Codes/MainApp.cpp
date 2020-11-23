#include "stdafx.h"
#include "MainApp.h"
#include "Logo.h"
#include "Player.h"

MainApp::MainApp()
	: m_pManagement(Management::Get_Instance())
{
	SafeAddRef(m_pManagement);
}

HRESULT MainApp::ReadyMainApp()
{
	if (FAILED(m_pManagement->ReadyEngine(g_hWnd, WINCX, WINCY,
		DisplayMode::WINDOW, (_uint)SceneID::End)))
	{
		LOG_MSG(L"Error", L"Preparation of Graphic_Device has Failed");
		return E_FAIL;
	}

	m_pDevice = m_pManagement->GetDevice();
	if (nullptr == m_pDevice)
	{
		return E_FAIL;
	}
	SafeAddRef(m_pDevice);

	if (FAILED(ReadyStaticResources()))
		return E_FAIL;

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
	m_pManagement->LateUpdateEngine();
	m_pManagement->RenderEngine();
	return 0;
}

HRESULT MainApp::ReadyStaticResources()
{
	/* GameObject */
#pragma region GameObject_Player
	if (FAILED(m_pManagement->AddGameObjectPrototype(
		(_int)SceneID::Static,
		L"GameObject_Player",
		Player::Create(m_pDevice))))
	{
		return E_FAIL;
	}
#pragma endregion

	/* Compnenet */
#pragma region Component_VIBuffer_TriColor
	if (FAILED(m_pManagement->AddComponentPrototype(
		(_int)SceneID::Static,
		L"Component_VIBuffer_TriColor",
		VIBuffer_TriColor::Create(m_pDevice))))
	{
		return E_FAIL;
	}
#pragma endregion

	return S_OK;
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
	SafeRelease(m_pDevice);
	SafeRelease(m_pManagement);
	Management::ReleaseEngine();
}

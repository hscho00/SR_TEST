#include "stdafx.h"
#include "MainApp.h"
#include "Logo.h"
#include "Player.h"
#include "Terrain.h"
#include "Camera.h"

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

	if (FAILED(ReadyDefaultSetting()))
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

#pragma region GameObject_Terrain
	if (FAILED(m_pManagement->AddGameObjectPrototype(
		(_int)SceneID::Static,
		L"GameObject_Terrain",
		Terrain::Create(m_pDevice)
	)))
	{
		return E_FAIL;
	}
#pragma endregion

	/* Compnenet */
#pragma region Component_VIBuffer_RectColor
	if (FAILED(m_pManagement->AddComponentPrototype(
		(_int)SceneID::Static,
		L"Component_VIBuffer_RectColor",
		VIBuffer_RectColor::Create(m_pDevice))))
		return E_FAIL;
#pragma endregion

#pragma region Component_VIBuffer_Terrain
	if (FAILED(m_pManagement->AddComponentPrototype(
		(_int)SceneID::Static,
		L"Component_VIBuffer_Terrain",
		VIBuffer_TerrainColor::Create(m_pDevice, 100, 100))))
		return E_FAIL;
#pragma endregion

	return S_OK;
}

HRESULT MainApp::ReadyDefaultSetting()
{
	/* 조명 오프 */
	if (FAILED(m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE)))
	{
		return E_FAIL;
	}
	
	/* 후면 추려내기 off */
	if (FAILED(m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)))
		return E_FAIL;
	/*
	D3DCULL_CW(ClockWise): 시계방향인 정점들을 추려낸다.
	D3DCULL_CCW(Counter ClockWise): 반시계방향인 정점들을 추려낸다. 디폴트.
	D3DCULL_NONE: 후면 추려내기 off
	*/

	/* 와이어 프레임 on */
	if (FAILED(m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME)))
		return E_FAIL;

	/*
	카메라
	*/

	D3DXMATRIX matView, matProj;

	PROJ Proj;

	Proj.fWidth = (float)WINCX;
	Proj.fHeight = (float)WINCY;
	Proj.fNear = 1.f;
	Proj.fFar = 1000.f;
	Proj.fFovy = D3DXToRadian(90.f);	// 시야각 D3DX_PI / 4.f;

	Camera::Get_Instance()->Create(
		m_pDevice,
		_vector3(0.f, 5.f, -5.f),	/* 월드 상 카메라 위치 Eye */
		_vector3(0.f, 0.f, 0.f),	/* 카메라가 바라보는 지점 At */
		Proj						/* Up 벡터 */
	);
	
	matView = Camera::Get_Instance()->Get_Transform(Camera::CameraCt::VIEW);
	if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &matView)))
		return E_FAIL;
	
	matProj = Camera::Get_Instance()->Get_Transform(Camera::CameraCt::PROJ);
	if (FAILED(m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj)))
		return E_FAIL;
	
	///* 뷰행렬 만드는 함수 */
	//D3DXMatrixLookAtLH(
	//	&matView, /* 반환 값 */
	//	&D3DXVECTOR3(0.f, 5.f, -5.f), /* 월드상 카메라 위치 Eye */
	//	&D3DXVECTOR3(0.f, 0.f, 0.f), /* 카메라가 바라보는 지점 At */
	//	&D3DXVECTOR3(0.f, 1.f, 0.f) /* Up벡터 */);

	//if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &matView)))
	//	return E_FAIL;

	///* 원근 투영 행렬을 만드는 함수 */
	//D3DXMatrixPerspectiveFovLH(
	//	&matProj, /* 반환 값 */
	//	D3DXToRadian(90.f), /* 시야각 FovY */
	//	float(WINCX) / WINCY, /* 종횡비 Aspect */
	//	1.f, /* 카메라와 근편명과의 Z거리 Near */
	//	1000.f /* 카메라와 원평면과의 Z거리 Far */);

	//if (FAILED(m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj)))
	//	return E_FAIL;


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
	Camera::Destroy_Instance();
	Management::ReleaseEngine();
}

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
	if (FAILED(ReadyDefaultSetting()))
		return E_FAIL;

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
													CVIBuffer_TriColor::Create(m_pDevice, D3DCOLOR_XRGB(255, 0, 0)))))
	{
		return E_FAIL;
	}
#pragma endregion

	return S_OK;
}

HRESULT CMainApp::ReadyDefaultSetting()
{
	/* 조명 off */
	if (FAILED(m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE)))
		return E_FAIL;

	/*
	D3DCULL_CW(ClockWise): 시계방향인 정점들을 추려낸다.
	D3DCULL_CCW(Counter ClockWise): 반시계방향인 정점들을 추려낸다. 디폴트.
	D3DCULL_NONE: 후면 추려내기 off
	*/
	if (FAILED(m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW)))
		return E_FAIL;

	/*
	D3DFILL_WIREFRAME: 와이어 프레임으로 폴리곤을 표현
	D3DFILL_SOLID: 디폴트
	*/
	if (FAILED(m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID)))
		return E_FAIL;

	//
	D3DXMATRIX matView;
	/* 뷰행렬 만드는 함수. LH는 왼손좌표계 */
	D3DXMatrixLookAtLH(&matView, /* 반환 값 */
					&D3DXVECTOR3(0.f, 5.f, -5.f), /* 월드상 카메라 위치 Eye */
					&D3DXVECTOR3(0.f, 0.f, 0.f), /* 카메라가 바라보는 지점 At */
					&D3DXVECTOR3(0.f, 1.f, 0.f) /* Up벡터 */);

	if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &matView)))
		return E_FAIL;

	//
	D3DXMATRIX matProj;
	/* 원근(Perspective. X, Y값을 Z로 나눠서 멀리있는 것은 작게 그림) 
	   투영(n차원을 n-1차원으로 만드는 과정) 행렬을 만드는 함수 */
	D3DXMatrixPerspectiveFovLH(&matProj, /* 반환 값 */
								D3DX_PI * 0.5f, /* 시야각(Field of View) FovY. 투영스페이스는 정사각형이기 때문에 X or Y 하나만 있어도 충분.*/
								(_float)WINCX / WINCY, /* 종횡비 Aspect */
								1.f, /* 카메라와 근편명과의 Z거리 Near. 0으로 나눌 수 없으므로 0은 X*/
								1000.f /* 카메라와 원평면과의 Z거리 Far */);

	if (FAILED(m_pDevice->SetTransform(D3DTS_PROJECTION, &matProj)))
		return E_FAIL;

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
#include "stdafx.h"
#include "MainApp.h"

#include "Logo.h"
#include "Player.h"


CMainApp::CMainApp()
	: m_pManagement(CManagement::Get_Instance())
	, m_pDevice(nullptr)
{
	// �ܺο��� ������ �����Ͱ� ������ ������ �����ʹ�,
	// �� �����͸� �ڱ⵵ �����Ѵ�(���������), �� AddRef() ������
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
	/* ���� off */
	if (FAILED(m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE)))
		return E_FAIL;

	/*
	D3DCULL_CW(ClockWise): �ð������ �������� �߷�����.
	D3DCULL_CCW(Counter ClockWise): �ݽð������ �������� �߷�����. ����Ʈ.
	D3DCULL_NONE: �ĸ� �߷����� off
	*/
	if (FAILED(m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW)))
		return E_FAIL;

	/*
	D3DFILL_WIREFRAME: ���̾� ���������� �������� ǥ��
	D3DFILL_SOLID: ����Ʈ
	*/
	if (FAILED(m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID)))
		return E_FAIL;

	//
	D3DXMATRIX matView;
	/* ����� ����� �Լ�. LH�� �޼���ǥ�� */
	D3DXMatrixLookAtLH(&matView, /* ��ȯ �� */
					&D3DXVECTOR3(0.f, 5.f, -5.f), /* ����� ī�޶� ��ġ Eye */
					&D3DXVECTOR3(0.f, 0.f, 0.f), /* ī�޶� �ٶ󺸴� ���� At */
					&D3DXVECTOR3(0.f, 1.f, 0.f) /* Up���� */);

	if (FAILED(m_pDevice->SetTransform(D3DTS_VIEW, &matView)))
		return E_FAIL;

	//
	D3DXMATRIX matProj;
	/* ����(Perspective. X, Y���� Z�� ������ �ָ��ִ� ���� �۰� �׸�) 
	   ����(n������ n-1�������� ����� ����) ����� ����� �Լ� */
	D3DXMatrixPerspectiveFovLH(&matProj, /* ��ȯ �� */
								D3DX_PI * 0.5f, /* �þ߰�(Field of View) FovY. ���������̽��� ���簢���̱� ������ X or Y �ϳ��� �־ ���.*/
								(_float)WINCX / WINCY, /* ��Ⱦ�� Aspect */
								1.f, /* ī�޶�� �������� Z�Ÿ� Near. 0���� ���� �� �����Ƿ� 0�� X*/
								1000.f /* ī�޶�� �������� Z�Ÿ� Far */);

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
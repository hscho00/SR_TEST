#include "stdafx.h"
#include "..\Headers\Stage.h"

#include "Layer.h"
#include "Player.h"


CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
    : CScene(pDevice)
    , m_pManagement(CManagement::Get_Instance())
    , m_pPlayer(nullptr)
{
    m_iSceneIndex = (_int)ESceneID::Stage;

    // �Ф�
    //SafeAddRef(m_pManagement);
}

HRESULT CStage::ReadyScene()
{
    // �������̵� �� �θ��� �Լ��� �� ȣ���� ����
    CScene::ReadyScene();

    PRINT_LOG(L"Stage", L"Stage");

    /////////////////////////////////////////////////
    // �÷��̾� ���̾� �߰�
    m_pManagement->AddLayer(m_iSceneIndex, L"Player", 1);

    // �÷��̾� ������Ÿ�� ����
    CPlayer* pPlayer = new CPlayer(m_pDevice);
    pPlayer->ReadyGameObjectPrototype();
    m_pManagement->AddObjPrototype(m_iSceneIndex, L"Player_0", pPlayer);

    // �÷��̾� Ŭ�� ����
    m_pPlayer = m_pManagement->CloneObjPrototype(m_iSceneIndex, L"Player_0");
    m_pManagement->AddObjInLayer(m_iSceneIndex, L"Player", m_pPlayer);

    // View Mat
    _vec3 cameraPos(0.f, 0.f, -5.f);
    _vec3 targetPos(0.f, 0.f, 0.f);
    _vec3 up(0.f, 1.f, 0.f);
    _matrix viewMat;
    D3DXMatrixLookAtLH(&viewMat, &cameraPos, &targetPos, &up);
    m_pDevice->SetTransform(D3DTS_VIEW, &viewMat);

    // Proj Mat
    _matrix projMat;
    D3DXMatrixPerspectiveFovLH(&projMat,
                                D3DX_PI * 0.5f,
                                (float)WINCX / (float)WINCY,
                                1.f,
                                1000.f);
    m_pDevice->SetTransform(D3DTS_PROJECTION, &projMat);

    // RenderState
    m_pDevice->SetRenderState(D3DRS_LIGHTING, false);

    return S_OK;
}

_uint CStage::UpdateScene()
{
	// �������̵� �� �θ��� �Լ��� �� ȣ���� ����
	CScene::UpdateScene();

    if (!m_pPlayer && (GetAsyncKeyState('Z') & 0x8000))
    {
        m_pPlayer = m_pManagement->GetObjInLayerOrNull(m_iSceneIndex, L"Player", 0);
        assert(m_pPlayer);
        m_pPlayer->Set_Using(true);
    }
    if (m_pPlayer && (GetAsyncKeyState('X') & 0x8000))
    {
        m_pPlayer->Set_Dead(true);
        m_pPlayer = nullptr;
    }

    m_pManagement->UpdateGameObject(m_iSceneIndex);

	return NO_EVENT;
}

_uint CStage::LateUpdateScene()
{
	// �������̵� �� �θ��� �Լ��� �� ȣ���� ����
	CScene::LateUpdateScene();

    m_pManagement->LateUpdateGameObject(m_iSceneIndex);

	return NO_EVENT;
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	CStage* pInstance = new CStage(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Stage");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void CStage::Free()
{
	// �������̵� �� �θ��� �Լ��� �� ȣ���� ����
	CScene::Free();

    //SafeRelease(m_pManagement);
}

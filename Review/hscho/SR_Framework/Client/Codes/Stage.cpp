#include "stdafx.h"
#include "..\Headers\Stage.h"


CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
    : CScene(pDevice)
    , m_pPlayer(nullptr)
{
    m_iSceneIndex = (_int)ESceneID::Stage;
}

HRESULT CStage::ReadyScene()
{
    // 오버라이딩 시 부모의 함수를 꼭 호출해 주자
    CScene::ReadyScene();

    PRINT_LOG(L"Stage", L"Stage");

    //
    if (FAILED(AddPlayerLayer(L"Layer_Player")))
        return E_FAIL;

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
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::UpdateScene();

	return NO_EVENT;
}

_uint CStage::LateUpdateScene()
{
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::LateUpdateScene();

    if (m_pPlayer)
    {
        if (!m_pPlayer->IsUsing() && (GetAsyncKeyState('Z') & 0x8000))
            m_pPlayer->Set_Using(true);
        else if (!m_pPlayer->IsDead() && (GetAsyncKeyState('X') & 0x8000))
            m_pPlayer->Set_Dead(true);
    }

	return NO_EVENT;
}

HRESULT CStage::AddPlayerLayer(const wstring& LayerTag)
{
    auto pManagement = CManagement::Get_Instance();
    assert(pManagement);

    if (FAILED(pManagement->AddLayer(m_iSceneIndex, LayerTag, 1)))
        return E_FAIL;

    if (FAILED(pManagement->AddGameObjectInLayer((_int)ESceneID::Static, L"GameObject_Player",
                                                (_int)ESceneID::Stage, LayerTag)))
        return E_FAIL;

    m_pPlayer = pManagement->GetGameObjectInLayerOrNull((_int)ESceneID::Stage, LayerTag, 0);
    assert(m_pPlayer);
    SafeAddRef(m_pPlayer);

    return S_OK;
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
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::Free();

    SafeRelease(m_pPlayer);
}

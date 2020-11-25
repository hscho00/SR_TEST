#include "stdafx.h"
#include "..\Headers\Stage.h"

#include "VIBuffer_QuadColor.h"
#include "VIBuffer_TerrainColor.h"
#include "Terrain.h"


CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
    : CScene(pDevice)
    , m_pPlayer(nullptr)
    /////////////////////////////////////
    , m_vCameraPos(_vec3(0.f, 5.f, -5.f))
    , m_vTargetPos(_vec3(0.f, 0.f, 0.f))
    , m_vUpVec(_vec3(0.f, 1.f, 0.f))
    , m_fCameraAngle(0.f)
    /////////////////////////////////////
{
    m_iSceneIndex = (_int)ESceneID::Stage;
}

HRESULT CStage::ReadyScene()
{
    // 오버라이딩 시 부모의 함수를 꼭 호출해 주자
    CScene::ReadyScene();

    PRINT_LOG(L"Stage", L"Stage");

    //
    auto pManagement = CManagement::Get_Instance();
    assert(pManagement);

    /* For.Component */
#pragma region Component_VIBuffer_QuadColor
    if (FAILED(pManagement->AddComponentPrototype(m_iSceneIndex,
        L"Component_VIBuffer_QuadColor",
        CVIBuffer_QuadColor::Create(m_pDevice, 0xffffffff))))
    {
        return E_FAIL;
    }
#pragma endregion

#pragma region Component_VIBuffer_TerrainColor
    if (FAILED(pManagement->AddComponentPrototype(m_iSceneIndex,
        L"Component_VIBuffer_TerrainColor",
        CVIBuffer_TerrainColor::Create(m_pDevice, 0xff008000, 50, 50))))
    {
        return E_FAIL;
    }
#pragma endregion

    /* For.GameObject */
#pragma region GameObject_Terrain
    if (FAILED(pManagement->AddGameObjectPrototype(m_iSceneIndex,
        L"GameObject_Terrain",
        CTerrain::Create(m_pDevice))))
    {
        return E_FAIL;
    }
#pragma endregion

    //
    if (FAILED(AddPlayerAndLayer()))
        return E_FAIL;
    //
    if (FAILED(AddTerrainAndLayer()))
        return E_FAIL;

    // View Mat
    _matrix viewMat;
    D3DXMatrixLookAtLH(&viewMat, &m_vCameraPos, &m_vTargetPos, &m_vUpVec);
    m_pDevice->SetTransform(D3DTS_VIEW, &viewMat);

    return S_OK;
}

_uint CStage::UpdateScene()
{
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::UpdateScene();

    /////////////////////////////////////////////
    if (m_pPlayer && m_pPlayer->IsUsing())
    {
        auto pManagement = CManagement::Get_Instance();
        assert(pManagement);

        _float speed = 50.f;
        if (GetAsyncKeyState('Q') & 0x8000)
            m_fCameraAngle += speed * pManagement->Get_DeltaTime();
        if (GetAsyncKeyState('E') & 0x8000)
            m_fCameraAngle -= speed * pManagement->Get_DeltaTime();
    }

    m_vTargetPos = m_pPlayer->Get_Pos();
    m_vCameraPos = m_vTargetPos + _vec3(5.f * sinf(D3DXToRadian(m_fCameraAngle)), 5.f, -5.f * cosf(D3DXToRadian(m_fCameraAngle)));

    _matrix viewMat;
    D3DXMatrixLookAtLH(&viewMat, &m_vCameraPos, &m_vTargetPos, &m_vUpVec);
    m_pDevice->SetTransform(D3DTS_VIEW, &viewMat);
    /////////////////////////////////////////////

	return NO_EVENT;
}

_uint CStage::LateUpdateScene()
{
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::LateUpdateScene();

    /////////////////////////////////////////////
    if (m_pPlayer)
    {
        if (!m_pPlayer->IsUsing() && (GetAsyncKeyState('Z') & 0x8000))
            m_pPlayer->Set_Using(true);
        else if (!m_pPlayer->IsDead() && (GetAsyncKeyState('X') & 0x8000))
        {
            m_pPlayer->Set_Dead(true);
            m_fCameraAngle = 0.f;
        }
    }
    /////////////////////////////////////////////

	return NO_EVENT;
}

HRESULT CStage::AddPlayerAndLayer()
{
    wstring LayerTag = L"Layer_Player";

    auto pManagement = CManagement::Get_Instance();
    assert(pManagement);

    if (FAILED(pManagement->AddLayer(m_iSceneIndex, LayerTag, 1)))
        return E_FAIL;

    if (FAILED(pManagement->AddGameObjectInLayer((_int)ESceneID::Static, L"GameObject_Player",
                                                m_iSceneIndex, LayerTag)))
        return E_FAIL;

    m_pPlayer = pManagement->GetGameObjectInLayerOrNull(m_iSceneIndex, LayerTag, 0);
    assert(m_pPlayer);
    SafeAddRef(m_pPlayer);

    return S_OK;
}

HRESULT CStage::AddTerrainAndLayer()
{
    wstring LayerTag = L"Layer_Terrain";

    auto pManagement = CManagement::Get_Instance();
    assert(pManagement);

    if (FAILED(pManagement->AddLayer(m_iSceneIndex, LayerTag, 1)))
        return E_FAIL;

    if (FAILED(pManagement->AddGameObjectInLayer(m_iSceneIndex, L"GameObject_Terrain",
                                                m_iSceneIndex, LayerTag)))
        return E_FAIL;

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
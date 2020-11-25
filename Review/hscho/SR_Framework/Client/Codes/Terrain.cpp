#include "stdafx.h"
#include "..\Headers\Terrain.h"

#include "Management.h"


CTerrain::CTerrain(LPDIRECT3DDEVICE9 pDevice)
    : CGameObject(pDevice)
    , m_pVIBufferCom(nullptr)
{

}

CTerrain::CTerrain(const CTerrain& other)
    : CGameObject(other)
    , m_pVIBufferCom(nullptr)    // Clone 할 때, AddComponent() 에서 추가
{

}

HRESULT CTerrain::ReadyGameObjectPrototype()
{
    if (FAILED(CGameObject::ReadyGameObjectPrototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CTerrain::ReadyGameObject(void* pArg)
{
    if (FAILED(CGameObject::ReadyGameObject(pArg)))
        return E_FAIL;

    if (FAILED(AddComponent()))
        return E_FAIL;

    //////////////////////////////////////////////////////////////
    // 나중에 Transform 생기면 수정
    //m_fAngle = 90.f;
    //m_vPos = _vec3(0.f, -3.f, 0.f);

    //_matrix matScale, matRotX, matTrans;
    //D3DXMatrixScaling(&matScale, 10.f, 10.f, 1.f);
    //D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngle));
    //D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);
    //m_matWorld = matScale * matRotX * matTrans;
    //////////////////////////////////////////////////////////////

    return S_OK;
}

_uint CTerrain::UpdateGameObject(_float fDeltaTime)
{
    _uint ret = CGameObject::UpdateGameObject(fDeltaTime);
    if (ret == OBJ_DEAD)
        return ret;

    return NO_EVENT;
}

_uint CTerrain::LateUpdateGameObject(_float fDeltaTime)
{
    _uint ret = CGameObject::LateUpdateGameObject(fDeltaTime);

    if (m_bDraw)
    {
        auto pManagement = CManagement::Get_Instance();
        assert(pManagement);

        if (FAILED(pManagement->AddGameObjectInRenderer(ERenderID::NoAlpha, this)))
            return ERROR;
    }

    return ret;
}

HRESULT CTerrain::RenderGameObject()
{
    if (FAILED(CGameObject::RenderGameObject()))
        return E_FAIL;

    //
    m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

    //
    m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

    //
    if (FAILED(m_pVIBufferCom->Render_VIBuffer()))
        return E_FAIL;

    //
    m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

    return S_OK;
}

HRESULT CTerrain::AddComponent()
{
    /* For.Com_VIBuffer */
    if (!m_pVIBufferCom)
    {
        if (FAILED(CGameObject::AddComponent((_int)ESceneID::Stage,
            L"Component_VIBuffer_TerrainColor",
            L"Com_VIBuffer",
            (CComponent**)&m_pVIBufferCom)))
        {
            return E_FAIL;
        }
    }

    return S_OK;
}

CTerrain* CTerrain::Create(LPDIRECT3DDEVICE9 pDevice)
{
    assert(pDevice);

    CTerrain* pInstance = new CTerrain(pDevice);
    if (FAILED(pInstance->ReadyGameObjectPrototype()))
    {
        PRINT_LOG(L"Warning", L"Failed To Create Terrain");
        SafeRelease(pInstance);
    }

    return pInstance;
}

CGameObject* CTerrain::Clone(void* pArg)
{
    CTerrain* pClone = new CTerrain(*this); /* 복사생성자 */
    if (FAILED(pClone->ReadyGameObject(pArg)))
    {
        PRINT_LOG(L"Warning", L"Failed To Clone Terrain");
        SafeRelease(pClone);
    }

    return pClone;
}

void CTerrain::Free()
{
    CGameObject::Free();

    SafeRelease(m_pVIBufferCom);
}


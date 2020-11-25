#include "stdafx.h"
#include "..\Headers\Player.h"

#include "Management.h"


CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
    : CGameObject(pDevice)
    , m_pVIBufferCom(nullptr)
{

}

CPlayer::CPlayer(const CPlayer& other)
    : CGameObject(other)
    , m_pVIBufferCom(nullptr)    // Clone 할 때, AddComponent() 에서 추가
{

}

HRESULT CPlayer::ReadyGameObjectPrototype()
{
    if (FAILED(CGameObject::ReadyGameObjectPrototype()))
        return E_FAIL;

    return S_OK;
}

HRESULT CPlayer::ReadyGameObject(void* pArg)
{
    if (FAILED(CGameObject::ReadyGameObject(pArg)))
        return E_FAIL;

    if (FAILED(AddComponent()))
        return E_FAIL;

    //////////////////////////////////////////////////////////////
    // 나중에 Transform 생기면 수정
    m_fAngle = 0.f;
    m_vPos = _vec3(0.f, 0.f, 0.f);
    //////////////////////////////////////////////////////////////

    return S_OK;
}

_uint CPlayer::UpdateGameObject(_float fDeltaTime)
{
    _uint ret = CGameObject::UpdateGameObject(fDeltaTime);
    if (ret == OBJ_DEAD)
        return ret;

    //////////////////////////////////////////////////////////////
    _float speed = 5.f;
    if (GetAsyncKeyState('W') & 0x8000)
        m_vPos.z += speed * fDeltaTime;
    if (GetAsyncKeyState('S') & 0x8000)
        m_vPos.z -= speed * fDeltaTime;
    if (GetAsyncKeyState('A') & 0x8000)
        m_vPos.x -= speed * fDeltaTime;
    if (GetAsyncKeyState('D') & 0x8000)
        m_vPos.x += speed * fDeltaTime;
    
    //
    m_fAngle -= 100.f * fDeltaTime;

    //
    _matrix matScale, matRotY, matTrans;
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);
    m_matWorld = matScale * matRotY * matTrans;
    //////////////////////////////////////////////////////////////

    return NO_EVENT;
}

_uint CPlayer::LateUpdateGameObject(_float fDeltaTime)
{
    _uint ret = CGameObject::LateUpdateGameObject(fDeltaTime);

    if (m_bDraw)    // 부모에서 하면 좋은데... Renderer 에 넣는걸 여기서 하니까 어쩔수 없을듯
    {
        auto pManagement = CManagement::Get_Instance();
        assert(pManagement);

        if (FAILED(pManagement->AddGameObjectInRenderer(ERenderID::NoAlpha, this)))
            return ERROR;
    }

    return ret;
}

HRESULT CPlayer::RenderGameObject()
{
    if (FAILED(CGameObject::RenderGameObject()))
        return E_FAIL;

    //
    m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
    m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    //
    if (FAILED(m_pVIBufferCom->Render_VIBuffer()))
        return E_FAIL;

    //
    m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // 디폴트 상태로

    return S_OK;
}

HRESULT CPlayer::AddComponent()
{
    /* For.Com_VIBuffer */
    if (!m_pVIBufferCom)
    {
        if (FAILED(CGameObject::AddComponent((_int)ESceneID::Static,
            L"Component_VIBuffer_TriColor",
            L"Com_VIBuffer",
            (CComponent**)&m_pVIBufferCom)))
        {
            return E_FAIL;
        }
    }

    return S_OK;
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
    assert(pDevice);

    CPlayer* pInstance = new CPlayer(pDevice);
    if (FAILED(pInstance->ReadyGameObjectPrototype()))
    {
        PRINT_LOG(L"Warning", L"Failed To Create Player");
        SafeRelease(pInstance);
    }

    return pInstance;
}

CGameObject* CPlayer::Clone(void* pArg)
{
    CPlayer* pClone = new CPlayer(*this); /* 복사생성자 */
    if (FAILED(pClone->ReadyGameObject(pArg)))
    {
        PRINT_LOG(L"Warning", L"Failed To Clone Player");
        SafeRelease(pClone);
    }

    return pClone;
}

void CPlayer::Free()
{
    CGameObject::Free();

    SafeRelease(m_pVIBufferCom);
}
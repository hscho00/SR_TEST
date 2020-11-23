#include "stdafx.h"
#include "..\Headers\Player.h"

#include "Management.h"


CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
    : CGameObject(pDevice)
    , m_pVIBufferCom(nullptr)
    , m_fAngle(0.f)
{

}

CPlayer::CPlayer(const CPlayer& other)
    : CGameObject(other)
    , m_pVIBufferCom(nullptr)    // Clone 할 때, AddComponent() 에서 추가
    , m_fAngle(other.m_fAngle)
{

}

HRESULT CPlayer::ReadyGameObjectPrototype()
{
    if (FAILED(CGameObject::ReadyGameObjectPrototype()))
        return E_FAIL;

    //
    m_fAngle = 0.f;
    m_vPos = _vec3(0.f, 0.f, 0.f);

    return S_OK;
}

HRESULT CPlayer::ReadyGameObject(void* pArg)
{
    if (FAILED(CGameObject::ReadyGameObject(pArg)))
        return E_FAIL;

    if (FAILED(AddComponent()))
        return E_FAIL;

    //
    m_fAngle = 0.f;
    m_vPos = _vec3(0.f, 0.f, 0.f);

    return S_OK;
}

_uint CPlayer::UpdateGameObject(float fDeltaTime)
{
    _uint ret = CGameObject::UpdateGameObject(fDeltaTime);
    if (ret == OBJ_DEAD)
        return ret;

    //
    float speed = 5.f;
    if (GetAsyncKeyState('W') & 0x8000)
        m_vPos.y += speed * fDeltaTime;
    if (GetAsyncKeyState('S') & 0x8000)
        m_vPos.y -= speed * fDeltaTime;
    if (GetAsyncKeyState('A') & 0x8000)
        m_vPos.x -= speed * fDeltaTime;
    if (GetAsyncKeyState('D') & 0x8000)
        m_vPos.x += speed * fDeltaTime;
    if (GetAsyncKeyState('Q') & 0x8000)
        m_vPos.z += speed * fDeltaTime;;
    if (GetAsyncKeyState('E') & 0x8000)
        m_vPos.z -= speed * fDeltaTime;
    
    //
    m_fAngle -= 100.f * fDeltaTime;

    //
    _matrix matScale, matRotZ, matTrans;
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);
    m_matWorld = matScale * matRotZ * matTrans;

    return NO_EVENT;
}

_uint CPlayer::LateUpdateGameObject(float fDeltaTime)
{
    _uint ret = CGameObject::LateUpdateGameObject(fDeltaTime);

    auto pManagement = CManagement::Get_Instance();
    assert(pManagement);

    if (FAILED(pManagement->AddGameObjectInRenderer(ERenderID::NoAlpha, this)))
        return ERROR;

    return ret;
}

HRESULT CPlayer::RenderGameObject()
{
    if (FAILED(CGameObject::RenderGameObject()))
        return E_FAIL;

    //
    m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);

    //
    if (FAILED(m_pVIBufferCom->Render_VIBuffer()))
        return E_FAIL;

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

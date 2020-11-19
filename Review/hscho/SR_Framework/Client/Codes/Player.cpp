#include "stdafx.h"
#include "..\Headers\Player.h"

//////////////////////
// 컴포넌트가 와야할 부분
#include "Vertices.h"
//////////////////////


CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
    : CGameObject(pDevice)
    , m_fAngle(0.f)
{
    m_vPos = _vec3(0.f, 0.f, 0.f);
}

HRESULT CPlayer::ReadyGameObjectPrototype()
{
    CGameObject::ReadyGameObjectPrototype();

    //
    m_fAngle = 0.f;
    m_vPos = _vec3(0.f, 0.f, 0.f);

    //
    Vertex vertices[3] = {};
    WORD indices[3] = {};
    vertices[0] = Vertex(-1.f, -1.f, 0.f, D3DCOLOR_XRGB(255, 0, 0));
    vertices[1] = Vertex(0.f, 1.f, 0.f, D3DCOLOR_XRGB(0, 0, 255));
    vertices[2] = Vertex(1.f, -1.f, 0.f, D3DCOLOR_XRGB(255, 255, 0));
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    m_pVertices = CVertices::Create(vertices, 3, indices, 4, 1);
    assert(m_pVertices);

    return S_OK;
}

HRESULT CPlayer::ReadyGameObject(void* pArg)
{
    CGameObject::ReadyGameObject(pArg);

    m_fAngle = 0.f;
    m_vPos = _vec3(0.f, 0.f, 0.f);

    return S_OK;
}

_uint CPlayer::UpdateGameObject(float fDeltaTime)
{
    _uint ret = CGameObject::UpdateGameObject(fDeltaTime);

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

    m_fAngle -= 100.f * fDeltaTime;

    _matrix matScale, matRotZ, matTrans;
    D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
    D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(m_fAngle));
    D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);
    m_matWorld = matScale * matRotZ * matTrans;

    return ret;
}

_uint CPlayer::LateUpdateGameObject(float fDeltaTime)
{
    return CGameObject::LateUpdateGameObject(fDeltaTime);;
}

HRESULT CPlayer::RenderGameObject()
{
    CGameObject::RenderGameObject();

    m_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
    m_pDevice->SetStreamSource(0, m_pVertices->Get_VertexBuffer(), 0, sizeof(Vertex));
    m_pDevice->SetIndices(m_pVertices->Get_IndexBuffer());
    m_pDevice->SetFVF(m_pVertices->Get_FVF());
    m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_pVertices->Get_VerticesCount(), 0, m_pVertices->Get_PrimCount());

    return S_OK;
}

CGameObject* CPlayer::Clone(void* pArg)
{
    // 복사생정자 이쁘게 만들면 될것 같은데...
    SafeAddRef(m_pDevice);
    return static_cast<CGameObject*>(new CPlayer(*this));
}

void CPlayer::Free()
{
    CGameObject::Free();
}

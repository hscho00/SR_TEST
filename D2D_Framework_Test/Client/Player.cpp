#include "stdafx.h"
#include "Player.h"
#include "Graphic_Device.h"
#include "Texture_Manager.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "ScrollManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ObjManager.h"
#include "Terrain.h"


CPlayer::CPlayer()
    : m_pTerrain(nullptr)
    , m_dwCurTileIdx(-1)
    , m_dwNextTileIdx(-1)
    , m_pCurTile(nullptr)
    , m_pUpTile(nullptr)
    , m_pDownTile(nullptr)
    , m_pLeftTile(nullptr)
    , m_pRightTile(nullptr)
    , m_vDstTilePos()
    , m_vTileMoveDir(_vec3(0.f, 0.f, 0.f))
    , m_fTileMoveDefaultSpeed(300.f)
    , m_fTileMoveSpeed(m_fTileMoveDefaultSpeed)
{
    m_ObjID = OBJ::ID::PLAYER;
    m_RenderGroup = OBJ::RENDER_GROUP::GAMEOBJECT;

    m_pObjectKey = L"Player";

    // 임시
    m_pStateKey = L"Walk_Down";
    m_frame.byCurFrame = 0;
    m_frame.byEndFrame = 3;
    m_frame.fResetFrameTime = 0.5f;
    m_eDir = OBJ::DIR::DOWN;
}

CPlayer::~CPlayer()
{
    Release();
}

HRESULT CPlayer::Init()
{

    return S_OK;
}

OBJ::EVENT CPlayer::Update()
{
    CheckKeyState();

    MovePlayer();
    ScrollOffset();

    FrameMove();

    return OBJ::EVENT::NO_EVENT;
}

void CPlayer::LateUpdate()
{

}

void CPlayer::Render()
{
    _matrix matScale, matTrans, matWorld;
    D3DXMatrixScaling(&matScale, m_vSize.x, m_vSize.y, 0.f);
    D3DXMatrixTranslation(&matTrans, m_vPos.x - CScrollManager::Get_Scroll(CScrollManager::SCROLL_X), m_vPos.y - CScrollManager::Get_Scroll(CScrollManager::SCROLL_Y), 0.f);
    matWorld = matScale * matTrans;

    LPD3DXSPRITE pSprite = CGraphic_Device::Get_Instance()->Get_Sprite();
    pSprite->SetTransform(&matWorld);

    const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(m_pObjectKey, m_pStateKey, m_frame.byCurFrame);
    assert(!(pTexInfo == nullptr));
    float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
    float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

    pSprite->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release()
{

}

void CPlayer::Init_Terrain(CObj* pTerrain)
{
    m_pTerrain = static_cast<CTerrain*>(pTerrain);
}

void CPlayer::Set_CurTile_Force(const DWORD idx)
{
    m_dwCurTileIdx = m_dwNextTileIdx = idx;
    CheckNextTile();
    m_pTerrain->Get_TileCenterPos(&m_vPos, idx);
}

void CPlayer::Set_NextTileIdx(const DWORD idx, OBJ::DIR dir)
{
    m_dwNextTileIdx = idx;

    switch (dir)
    {
    case OBJ::DIR::LEFT:
        m_vTileMoveDir = _vec3(-1.f, 0.f, 0.f);
        break;
    case OBJ::DIR::RIGHT:
        m_vTileMoveDir = _vec3(1.f, 0.f, 0.f);
        break;
    case OBJ::DIR::UP:
        m_vTileMoveDir = _vec3(0.f, -1.f, 0.f);
        break;
    case OBJ::DIR::DOWN:
        m_vTileMoveDir = _vec3(0.f, 1.f, 0.f);
        break;
    }
 
    m_vDstTilePos = m_vPos;
    m_pTerrain->Get_TileCenterPos(&m_vDstTilePos, m_dwNextTileIdx);
}

void CPlayer::CheckKeyState()
{
    if (m_dwCurTileIdx == m_dwNextTileIdx)
    {
        CheckKeyState_Move();
    }
}

void CPlayer::CheckKeyState_Move()
{
    CKeyManager* pKeyMgr = CKeyManager::Get_Instance();

    // 캐릭터 방향
    if (pKeyMgr->IsKeyPressing(CKeyManager::LEFT))
    {
        m_eDir = OBJ::DIR::LEFT;
        m_pStateKey = L"Walk_Left";
    }
    else if (pKeyMgr->IsKeyPressing(CKeyManager::RIGHT))
    {
        m_eDir = OBJ::DIR::RIGHT;
        m_pStateKey = L"Walk_Right";
    }
    else if (pKeyMgr->IsKeyPressing(CKeyManager::UP))
    {
        m_eDir = OBJ::DIR::UP;
        m_pStateKey = L"Walk_Up";
    }
    else if (pKeyMgr->IsKeyPressing(CKeyManager::DOWN))
    {
        m_eDir = OBJ::DIR::DOWN;
        m_pStateKey = L"Walk_Down";
    }

    // 다음타일 설정
    if (m_pLeftTile && pKeyMgr->IsKeyPressing(CKeyManager::LEFT))
    {
        // Left Tile로 이동!
        Set_NextTileIdx(m_pLeftTile->dwIndex, OBJ::DIR::LEFT);
    }
    else if (m_pRightTile && pKeyMgr->IsKeyPressing(CKeyManager::RIGHT))
    {
        // Right Tile로 이동!
        Set_NextTileIdx(m_pRightTile->dwIndex, OBJ::DIR::RIGHT);
    }
    else if (m_pUpTile && pKeyMgr->IsKeyPressing(CKeyManager::UP))
    {
        // Up Tile로 이동!
        Set_NextTileIdx(m_pUpTile->dwIndex, OBJ::DIR::UP);
    }
    else if (m_pDownTile && pKeyMgr->IsKeyPressing(CKeyManager::DOWN))
    {
        // Down Tile로 이동!
        Set_NextTileIdx(m_pDownTile->dwIndex, OBJ::DIR::DOWN);
    }
}

void CPlayer::MovePlayer()
{
    if (m_dwCurTileIdx != m_dwNextTileIdx)
    {
        _vec3 vTemp = m_vDstTilePos - m_vPos;
        if (D3DXVec3Length(&vTemp) < 10.f)   // NextTile에 거의 도착했을 때
        {
            m_vPos = m_vDstTilePos;
            m_fTileMoveSpeed = m_fTileMoveDefaultSpeed;
            m_dwCurTileIdx = m_dwNextTileIdx;

            CheckNextTile();    // CurTile 갱신
        }
        else
        {
            // fDeltaTime이 너무 커서(실행하자 마자 라던가...) 한 프레임에 너무 많이 움직일수 있으므로 값을 제한
            float fDeltaTime = CTimeManager::Get_Instance()->Get_DeltaTime() < 0.15f ? CTimeManager::Get_Instance()->Get_DeltaTime() : 0.15f;

            m_vPos += m_vTileMoveDir * m_fTileMoveSpeed * fDeltaTime;
        }
    }
}

void CPlayer::CheckNextTile()
{
    assert(m_pTerrain);

    m_pCurTile = m_pTerrain->Get_VecTile()[m_dwCurTileIdx];

    DWORD tileXCnt = m_pTerrain->Get_TileCntX();
    DWORD tileYCnt = m_pTerrain->Get_TileCntY();

    DWORD tempIdx = m_dwNextTileIdx - tileXCnt;
    if (m_dwNextTileIdx < tileXCnt)     // DWORD 무조건 양수...
        m_pUpTile = nullptr;
    else
        m_pUpTile = m_pTerrain->Get_VecTile()[tempIdx];

    tempIdx = m_dwNextTileIdx + tileXCnt;
    if (tempIdx > tileXCnt * tileYCnt - 1)
        m_pDownTile = nullptr;
    else
        m_pDownTile = m_pTerrain->Get_VecTile()[tempIdx];

    tempIdx = m_dwNextTileIdx - 1;
    if ((tempIdx / tileXCnt) != (m_dwNextTileIdx / tileXCnt))
        m_pLeftTile = nullptr;
    else
        m_pLeftTile = m_pTerrain->Get_VecTile()[tempIdx];

    tempIdx = m_dwNextTileIdx + 1;
    if ((tempIdx / tileXCnt) != (m_dwNextTileIdx / tileXCnt))
        m_pRightTile = nullptr;
    else
        m_pRightTile = m_pTerrain->Get_VecTile()[tempIdx];
}

void CPlayer::ScrollOffset()
{
    float fScrollX = CScrollManager::Get_Scroll(CScrollManager::SCROLL_X);
    float fOffsetX = float(WINCX >> 1);

    float fScrollY = CScrollManager::Get_Scroll(CScrollManager::SCROLL_Y);
    float fOffsetY = float(WINCY >> 1);

    //float range = 0.f;

    if (fOffsetX > m_vPos.x - fScrollX)
        CScrollManager::Accumulate_ScrollX((m_vPos.x - fScrollX) - fOffsetX);
    else if (fOffsetX < m_vPos.x - fScrollX)
        CScrollManager::Accumulate_ScrollX((m_vPos.x - fScrollX) - fOffsetX);

    if (fOffsetY > m_vPos.y - fScrollY)
        CScrollManager::Accumulate_ScrollY((m_vPos.y - fScrollY) - fOffsetY);
    else if (fOffsetY < m_vPos.y - fScrollY)
        CScrollManager::Accumulate_ScrollY((m_vPos.y - fScrollY) - fOffsetY);
}
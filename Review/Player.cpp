#include "stdafx.h"
#include "Player.h"
#include "Key_Manager.h"
#include "Collision_Manager.h"
#include "GameObject_Manager.h"
#include "Line_Manager.h"
#include "PlayerBullet.h"
#include "Skul.h"
#include "Pessive.h"
#include "Scene_Manager.h"
#include "SoundMgr.h"
CPlayer::CPlayer()
	:m_State(P_IDLE)
	, m_fFallPower(5.f), m_iAttackCount(0), m_bDash(false)
	, m_fDashPower(0.f), m_fy(0), m_iDashCount(0), m_iDoubleJump(0)
	, m_vSkul_Pos(CGameObject_Manager::Get_Instance()->Get_Skul_Pos())
	, m_iWarlock_Charge(0), m_bWarlock_Skill(false), m_iWarlock_Charge2(0)
	, m_iA(255), m_fHitTime(0.f), m_bHit(false)
	
	

{
	m_bDirCheck = true;
	m_bJump = false;
	m_bJumpbutoon = true;
	m_bDoubleJumpButton = true;
	m_bDoubleJump = false;
	m_bFall = false;
	m_bPessive = false;
	m_bAmp = false;
	m_fJumpTime = 0.f;
	m_fJumpOption = 0.f;
	m_fDoubleJumpOption = 0.f;
	m_fDoubleJumpTime = 0.f;
	m_fFallTime = 0.f;
	m_bEndAnim = false;
	m_fJumpPower = 50.f;
	m_fDoubleJump = 0.f;
	m_iSkill_1_Count = 0;
	m_iPessive_Count = 0;
	m_fTest = 0.f;
	m_Skul_State = SKUL_NOMAL1;
	m_fAmptime = 0.f;
	m_iAmp_Count = 0;
}


CPlayer::~CPlayer()
{
}
void CPlayer::FrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	
	if (m_Skul_State != SKUL_GUARD && m_Skul_State != SKUL_WARLOCK)
	{
		if (m_State == P_ATTACK_1&& m_bDirCheck == true && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			if (m_iAttackCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_State = P_ATTACK_2;
			}
			else
			{
				m_State = P_IDLE;
				m_tFrame.fStartFrame = 0.f;
				m_iAttackCount = 0;
			}
		}
		else if (m_State == P_ATTACK_2 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_IDLE;
			m_iAttackCount = 0;
		}

		if (m_State == P_ATTACK_1 && m_bDirCheck == false && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			if (m_iAttackCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_State = P_ATTACK_2;
			}
			else
			{
				m_State = P_IDLE;
				m_tFrame.fStartFrame = 0.f;
				m_iAttackCount = 0;
			}
		}

		else if (m_State == P_ATTACK_2&& m_bDirCheck == false && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_IDLE;
			m_iAttackCount = 0;
		}

		if (m_State == P_JUMP_ATTACK &&m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_FALL;
		}

		if (m_State == P_DASH && m_tFrame.fStartFrame <= m_tFrame.fEndFrame)
		{
			if (m_iDashCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_bDash = true;
			}
			else
			{
				m_iDashCount = 0;
				m_iDoubleJump = 0;
			}
		}

		if (m_State == P_SKILL_1 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_IDLE;
		}

		if (m_State == P_SKILL_2 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
			m_State = P_SKILL_2_2;
		}
		if (m_State == P_SKILL_2_2 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{

			m_State = P_IDLE;
			m_tFrame.fStartFrame = 0.f;

		}


	}

	else if (m_Skul_State == SKUL_GUARD)
	{
		if (m_State == P_SKILL_2 && m_tFrame.fStartFrame >= m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
			m_State = P_IDLE;
		}
		if (m_State == P_ATTACK_1&& m_bDirCheck == true && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			if (m_iAttackCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_State = P_ATTACK_2;
			}
			else
			{
				m_State = P_IDLE;
				m_tFrame.fStartFrame = 0.f;
				m_iAttackCount = 0;
			}
		}
		else if (m_State == P_ATTACK_2 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_IDLE;
			m_iAttackCount = 0;
		}

		if (m_State == P_ATTACK_1 && m_bDirCheck == false && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			if (m_iAttackCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_State = P_ATTACK_2;
			}
			else
			{
				m_State = P_IDLE;
				m_tFrame.fStartFrame = 0.f;
				m_iAttackCount = 0;
			}
		}

		else if (m_State == P_ATTACK_2&& m_bDirCheck == false && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_IDLE;
			m_iAttackCount = 0;
		}

		if (m_State == P_JUMP_ATTACK &&m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_FALL;
		}

		if (m_State == P_DASH && m_tFrame.fStartFrame <= m_tFrame.fEndFrame)
		{
			if (m_iDashCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_bDash = true;
			}
			else
			{
				m_iDashCount = 0;
				m_iDoubleJump = 0;
			}
		}

		if (m_State == P_SKILL_1 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
			m_State = P_SKILL_1_2;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Atk_Sword_Large [Slash Up].wav", CSoundMgr::EFFECT);
		}

		else if (m_State == P_SKILL_1_2 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
			m_State = P_SKILL_1_3;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Atk_Sword_Large [Slash Up].wav", CSoundMgr::EFFECT);
		}
		else if (m_State == P_SKILL_1_3 && m_tFrame.fStartFrame >= m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
			m_State = P_IDLE;
		
		}
	}
	
	if (m_Skul_State == SKUL_WARLOCK)
	{
		if (m_State == P_ATTACK_1&& m_bDirCheck == true && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			if (m_iAttackCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_State = P_ATTACK_2;
			}
			else
			{
				m_State = P_IDLE;
				m_tFrame.fStartFrame = 0.f;
				m_iAttackCount = 0;
			}
		}
		else if (m_State == P_ATTACK_2 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_IDLE;
			m_iAttackCount = 0;
			m_tFrame.fStartFrame = 0.f;
		}

		if (m_State == P_ATTACK_1 && m_bDirCheck == false && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			if (m_iAttackCount > 1)
			{
				m_tFrame.fStartFrame = 0.f;
				m_State = P_ATTACK_2;
			}
			else
			{
				m_State = P_IDLE;
				m_tFrame.fStartFrame = 0.f;
				m_iAttackCount = 0;
			}
		}

		else if (m_State == P_ATTACK_2&& m_bDirCheck == false && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_State = P_IDLE;
			m_iAttackCount = 0;
			m_tFrame.fStartFrame = 0.f;
		}

		if (m_State == P_SKILL_1_CHARGE && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;	
		}
		if (m_State == P_SKILL_1_CHARGE_COMPLETED && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
			m_State = P_IDLE;
		}

		if (m_State == P_SKILL_2_CHARGE && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
		}
		if (m_State == P_SKILL_2_CHARGE_COMPLETED && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
		{
			m_tFrame.fStartFrame = 0.f;
			m_State = P_IDLE;
		}
	
		
	}


	
	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f;
		m_iAttackCount = 0;
		m_iDashCount = 0;
	}

}

void CPlayer::EffectFrame(float fSpeed)
{
	m_Effect_Frame.fStartFrame += m_Effect_Frame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

	if (m_Effect == E_SKILL_1 && m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
		m_Effect = E_SKILL_2;
	}
	else if (m_Effect == E_SKILL_2 && m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
		m_Effect = E_SKILL_3;
	}
	else if (m_Effect == E_SKILL_3 && m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
		m_Effect = E_SKILL_IDLE;
	}

	if (m_Effect == E_SKILL2_1 && m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
		m_Effect = E_SKILL2_2;
	}
	else if (m_Effect == E_SKILL2_2 && m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
		m_Effect = E_SKILL2_3;
	}
	else if (m_Effect == E_SKILL2_3 && m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
		m_Effect = E_SKILL_IDLE;
	}


	if (m_Effect == E_ATTACK && m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
		m_Effect = E_SKILL_IDLE;
	}


	if (m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;
	}
}

CPlayer * CPlayer::Create(float _x, float _y)
{
	CPlayer* pInstance = new CPlayer; 
	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance; 
		pInstance = nullptr; 
	}
	pInstance->m_tInfo.vPos = { _x,_y,0.f };
	return pInstance;
}

void CPlayer::Free()
{
	
}


void CPlayer::Image(P_STATE _eState,const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame, bool _dir)
{
	if (_dir == true)
	{
		if (m_State == _eState)
		{
		

			if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
				m_tFrame.fStartFrame = 0.f;
			m_tFrame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iA, 255, 255, 255));
		}
	}
	else
	{
		if (m_State == _eState)
		{
			if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
				m_tFrame.fStartFrame = 0.f;
			m_tFrame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iA, 255, 255, 255));
		}
	}
}

void CPlayer::Image(P_STATE _eState, const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame, bool _dir, float _y)
{
	if (_dir == true)
	{
		if (m_State == _eState)
		{
			if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
				m_tFrame.fStartFrame = 0.f;
			m_tFrame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (m_tInfo.vPos.y - _y) - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iA, 255, 255, 255));
		}
	}
	else
	{
		if (m_State == _eState)
		{
			if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
				m_tFrame.fStartFrame = 0.f;
			m_tFrame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (m_tInfo.vPos.y - _y) - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iA, 255, 255, 255));
		}
	}
}

void CPlayer::Image_Effect(SKILL_EFFECT _eState, const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame, bool _dir)
{
	if (_dir == true)
	{
		if (m_Effect == _eState)
		{

			
			m_Effect_Frame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_Effect_Frame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	else
	{
		if (m_Effect == _eState)
		{
		
			m_Effect_Frame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_Effect_Frame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CPlayer::Image_Effect(SKILL_EFFECT _eState, const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame, bool _dir, float _x, float _y)
{
	if (_dir == true)
	{
		if (m_Effect == _eState)
		{


			m_Effect_Frame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_Effect_Frame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, (m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)) + _x, (m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) + _y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
	else
	{
		if (m_Effect == _eState)
		{

			m_Effect_Frame.fEndFrame = EndFrame;
			const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_Effect_Frame.fStartFrame));
			if (nullptr == pTexInfo)
				return;
			float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
			float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

			_matrix matScale, matTrans, matWolrd;
			D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
			D3DXMatrixTranslation(&matTrans, (m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X)) - _x, (m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) + _y), 0.f);

			matWolrd = matScale * matTrans;

			CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
			CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CPlayer::OffSet()
{
	_vec3 vScrollX = { CScroll_Manager::Get_Instance()->Get_Scroll().x,0.f,0.f };
	float fOffSetX = float(WINCX >> 1);

	if (fOffSetX < m_tInfo.vPos.x + vScrollX.x)
		CScroll_Manager::Get_Instance()->Set_ScrollX(fOffSetX - (m_tInfo.vPos.x - vScrollX.x));
	if (fOffSetX > m_tInfo.vPos.x + vScrollX.x)
		CScroll_Manager::Get_Instance()->Set_ScrollX(fOffSetX - (m_tInfo.vPos.x - vScrollX.x));



	
	
}

int CPlayer::behavior()
{
	float fTimeDelta = CTime_Manager::Get_Instance()->Get_TimeDelta();
	float fSpeed = 150.f * fTimeDelta;
	//////////////////////////////////이동////////////////////////
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_RIGHT)
		&& m_State != P_DASH)
	{
		m_tInfo.vPos = _vec3({ (m_tInfo.vPos.x + fSpeed),m_tInfo.vPos.y,0.f });
		CScroll_Manager::Set_Scroll({ fSpeed,0.f,0.f });
		m_bDirCheck = true;
		if(m_State != P_SKILL_1_CHARGE && m_State != P_SKILL_1_CHARGE_COMPLETED
			&& m_State != P_SKILL_2_CHARGE && m_State != P_SKILL_2_CHARGE_COMPLETED)
		m_State = P_STATE::P_WALK;
	}
	if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_LEFT)
		 && m_State != P_DASH)
	{
		m_tInfo.vPos = _vec3({ (m_tInfo.vPos.x - fSpeed),m_tInfo.vPos.y,0.f });
		CScroll_Manager::Set_Scroll({ -fSpeed,0.f,0.f });
		m_bDirCheck = false;
		if (m_State != P_SKILL_1_CHARGE && m_State != P_SKILL_1_CHARGE_COMPLETED
			&& m_State != P_SKILL_2_CHARGE && m_State != P_SKILL_2_CHARGE_COMPLETED)
			m_State = P_STATE::P_WALK;
	}
	///////////////////////////기본 공격///////////////////////////

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_X))
	{	
		
		if (m_iAttackCount < 1)
			m_State = P_STATE::P_ATTACK_1;
		++m_iAttackCount;

		RECT Attack_Rect;

		Attack_Rect.left = (LONG)(m_tInfo.vPos.x) - 100;
		Attack_Rect.top = (LONG)(m_tInfo.vPos.y) - 100;
		Attack_Rect.right = (LONG)(m_tInfo.vPos.x) + 100;
		Attack_Rect.bottom = (LONG)(m_tInfo.vPos.y) + 100;
	

		if (m_Skul_State == SKUL_ROCKSTAR)
		{
			m_iPessive_Count += 3;
			m_Effect = E_ATTACK;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ATTACK);
			CSoundMgr::Get_Instance()->PlaySound(L"RockStar_Amp_Beat.wav", CSoundMgr::ATTACK);
		}
		else if (m_Skul_State == SKUL_WARLOCK)
		{
			CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_P_BULLET, Create_Attack<CPlayerBullet>(m_bDirCheck, m_Skul_State));
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ATTACK);
			CSoundMgr::Get_Instance()->PlaySound(L"Atk_Flame_Small.wav", CSoundMgr::ATTACK);
		}
		else if (m_Skul_State == SKUL_NOMAL1 || m_Skul_State ==SKUL_NOMAL2)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ATTACK);
			CSoundMgr::Get_Instance()->PlaySound(L"Skul_Atk 1.wav", CSoundMgr::ATTACK);
		}
		else if (m_Skul_State == SKUL_GUARD)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ATTACK);
			CSoundMgr::Get_Instance()->PlaySound(L"Atk_Sword_Large [Slash Up].wav", CSoundMgr::ATTACK);
		}
	}

	///////////////////////////점프////////////////////////////
	if (CKey_Manager::Get_Instance()->Key_Down(KEY_C))
	{
		if (P_STATE::P_JUMP != m_State && m_iDoubleJump <1)
		{
			m_State = P_STATE::P_JUMP;
			m_bJump = true;
			m_fJumpOption = m_tInfo.vPos.y;
			m_fJumpTime = 0.f;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::JUMP);
			CSoundMgr::Get_Instance()->PlaySound(L"Default_Jump.wav", CSoundMgr::JUMP);
		}
		else if(m_iDoubleJump ==1)
		{
			m_fJumpOption = m_tInfo.vPos.y;
			m_fJumpTime = 0.f;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::JUMP);
			CSoundMgr::Get_Instance()->PlaySound(L"Default_Jump.wav", CSoundMgr::JUMP);
		}


		++m_iDoubleJump;
	}
	///////////////////////////대쉬/////////////////////////////
	if (CKey_Manager::Get_Instance()->Key_Down(KEY_Z))
	{
		if (m_iDashCount < 1)
		{
			m_State = P_DASH;
			m_bDash = true;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::DASH);
			CSoundMgr::Get_Instance()->PlaySound(L"Default_Dash_Small.wav", CSoundMgr::DASH);
		}
		++m_iDashCount;
	}

	////////////////////////////////스킬//////////////////
	if (m_Skul_State == SKUL_NOMAL1 || m_Skul_State == SKUL_NOMAL2)
	{
		if (CKey_Manager::Get_Instance()->Key_Down(KEY_A))
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::ATTACK);
			CSoundMgr::Get_Instance()->PlaySound(L"Skul_Atk 1.wav", CSoundMgr::ATTACK);
			if (m_iSkill_1_Count == 0)
			{
				m_State = P_SKILL_1;

				CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_P_BULLET, Create_Skill<CPlayerBullet>(m_bDirCheck, m_Skul_State));
				++m_iSkill_1_Count;
				m_Skul_State = SKUL_NOMAL2;
			}

		}
		if (CKey_Manager::Get_Instance()->Key_Down(KEY_S) && m_iSkill_1_Count > 0)
		{
			m_State = P_SKILL_2;
			m_tInfo.vPos = CGameObject_Manager::Get_Instance()->Get_Head_Pos();
			m_iSkill_1_Count = 0;
			m_Skul_State = SKUL_NOMAL1;
			CGameObject_Manager::Get_Instance()->Set_Dead();
		}
	
	}
	if (m_Skul_State == SKUL_ROCKSTAR)
	{
		if (CKey_Manager::Get_Instance()->Key_Down(KEY_A) && m_iAmp_Count < 3)
		{
			m_State = P_SKILL_1;
			m_bAmp = true;
			CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_P_BULLET, Create_Skill<CPlayerBullet>(m_bDirCheck, m_Skul_State));
			++m_iAmp_Count;

			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"RockStar_BasicAttack.wav", CSoundMgr::EFFECT);
		}
	}

	if (m_Skul_State == SKUL_GUARD)
	{
		if (CKey_Manager::Get_Instance()->Key_Down(KEY_A))
		{
			m_State = P_SKILL_1;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Atk_Sword_Large [Slash Up].wav", CSoundMgr::EFFECT);
		}

		if (CKey_Manager::Get_Instance()->Key_Down(KEY_S))
		{
			
			m_State = P_SKILL_2;
			m_Effect = E_SKILL2_1;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"Atk_Flame_Large 2.wav", CSoundMgr::EFFECT);
			CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_P_BULLET, Create_Skill<CPlayerBullet>(m_bDirCheck, m_Skul_State));
		}
	}

	if (m_Skul_State == SKUL_WARLOCK)
	{
		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_A))
		{
			if(m_iWarlock_Charge <1)
				m_Effect = E_SKILL_1;
			m_State = P_SKILL_1_CHARGE;
			
			++m_iWarlock_Charge;
		}
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_A) && m_iWarlock_Charge >= 100)
		{
			m_State = P_SKILL_1_CHARGE_COMPLETED;
			m_iWarlock_Charge = 0;
			CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_P_BULLET, Create_Skill<CPlayerBullet>(m_tInfo.vPos.x,m_tInfo.vPos.y,m_bDirCheck, m_Skul_State, E_SKILL_1));
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"HighWarlock_Orb_Explosion_completed.wav", CSoundMgr::EFFECT);
		}
	
		if (CKey_Manager::Get_Instance()->Key_Pressing(KEY_S))
		{
			if (m_iWarlock_Charge2 <1)
				m_Effect = E_SKILL2_1;
			m_State = P_SKILL_2_CHARGE;

			++m_iWarlock_Charge2;
		}
		if (CKey_Manager::Get_Instance()->Key_Up(KEY_S) && m_iWarlock_Charge2 >= 100)
		{
			m_State = P_SKILL_2_CHARGE_COMPLETED;
			m_iWarlock_Charge2 = 0;
			CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_P_BULLET, Create_Skill<CPlayerBullet>(m_tInfo.vPos.x,0.f,m_bDirCheck, m_Skul_State, E_SKILL2_1));
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
			CSoundMgr::Get_Instance()->PlaySound(L"HighWarlock_Meteor_completed_Spawn.wav", CSoundMgr::EFFECT);
		}
	}

	////////////////////////////////////////////////////////////

	if (m_bJump == true && GetAsyncKeyState('X'))
	{
		m_State = P_JUMP_ATTACK;
	}

	if (CKey_Manager::Get_Instance()->Key_Down(KEY_SP))
	{
		
		SKUL Temp = m_Skul_State;
		m_Skul_State = m_Skul_Temp;
		m_Skul_Temp = Temp;


	}

	return 0;
}

void CPlayer::Jumping()
{
	bool bLineCol = CLine_Manager::Get_Instance()->CollisionLine(m_tInfo.vPos.x, &m_fy);

	if (bLineCol)
	{
		
	}
	m_tInfo.vPos.y += m_fFallPower;

	//float Test = m_tInfo.vPos.y - m_fy;
	if (bLineCol&& m_fy + 3.f < m_tInfo.vPos.y)
		m_tInfo.vPos.y = m_fy;

	if (m_bFall)
	{
		m_tInfo.vPos.y = m_fJumpOption - (m_fFallPower * m_fFallTime - 9.8f * m_fFallTime * m_fFallTime * 0.5f);
		m_fFallTime += 0.2f;


		if (m_State == P_WALK || m_State == P_IDLE)
			m_State = P_FALL;
		else if (m_State == P_WALK || m_State == P_IDLE)
			m_State = P_FALL;

		if (m_tInfo.vPos.y > m_fy)
		{
			m_tInfo.vPos.y = m_fy;
			m_bFall = false;
			m_fFallTime = 0.f;

			if (m_State == P_FALL)
				m_State = P_IDLE;
		}
	}
	if (m_bJump)
	{
	/*	if (m_iDoubleJump <=1)
		{*/
			m_tInfo.vPos.y = m_fJumpOption - (m_fJumpPower * m_fJumpTime - 9.8f * m_fJumpTime * m_fJumpTime * 0.5f);
			m_fJumpTime += 0.2f;
		//}
	
		if (m_State == P_WALK || m_State == P_IDLE)
			m_State = P_JUMP;

		if (bLineCol && m_fy+1 < m_tInfo.vPos.y)
		{
			m_bJump = false;
			m_tInfo.vPos.y = m_fy;
			m_fJumpTime = 0.f;
			m_fJumpPower = 50.f;
			m_bJumpbutoon = true;
			m_iDoubleJump = 0;
			if (m_State == P_JUMP || m_State == P_FALL) 
				m_State = P_IDLE;
		}
	}



	

}

void CPlayer::Dash()
{
	bool bLineCol = CLine_Manager::Get_Instance()->CollisionLine(m_tInfo.vPos.x, &m_fy);

	if (m_bDash && m_bDirCheck == true)
	{
		m_fDashPower += 1.5f;
		if (m_fDashPower < 18)
		{
			m_tInfo.vPos.x += m_fDashPower;
			CScroll_Manager::Set_Scroll({ m_fDashPower,0.f,0.f });
		}
		else if (m_fDashPower > 18)
		{
			m_State = P_FALL;
			m_fDashPower = 0.f;

			m_bJump = false;
			m_tInfo.vPos.y += 1.5f;
			m_fJumpTime = 0.f;
			m_fJumpPower = 50.f;
			m_bJumpbutoon = true;

			m_bDash = false;
			float Test = m_tInfo.vPos.y - m_fy;
		}
	}
	
	else if (m_bDash && m_bDirCheck == false)
	{
		m_fDashPower -= 1.5f;

		if (m_fDashPower > -18)
		{
			m_tInfo.vPos.x += m_fDashPower;
			CScroll_Manager::Set_Scroll({m_fDashPower, 0.f, 0.f});
		}
		else if (m_fDashPower < -18)
		{
			m_State = P_FALL;
			m_fDashPower = 0.f;

			m_bJump = false;
			m_tInfo.vPos.y += 1.5f;
			m_fJumpTime = 0.f;
			m_fJumpPower = 50.f;
			m_bJumpbutoon = true;

			m_bDash = false;
			float Test = m_tInfo.vPos.y - m_fy;
		}
		
	}
	if (bLineCol && m_fy < m_tInfo.vPos.y)
	{
		m_iDoubleJump = 0;
	}

}

void CPlayer::Skill_Pessive()
{
	if (m_Skul_State == SKUL_ROCKSTAR && m_iPessive_Count >=70 && m_bPessive==false)
	{
		m_bPessive = true;
		m_iPessive_Count = 0;

		CGameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_PESSIVE, Create_Pessive<CPessive>(m_tInfo.vPos.x,m_tInfo.vPos.y -15.f));
	}
		
	if (m_bPessive == true)
	{
		m_fTest += CTime_Manager::Get_Instance()->Get_TimeDelta();

		if (m_fTest > 12.f)
		{
			CGameObject_Manager::Get_Instance()->Set_Dead_Pessive();
			m_fTest = 0.f;
			m_iPessive_Count = 0;
			m_bPessive = false; 
		}
		
	}
}

void CPlayer::Skill_Amp()
{
	if (m_bAmp == true)
	{
		m_fAmptime += CTime_Manager::Get_Instance()->Get_TimeDelta();
		
	
		
		if (m_fAmptime > 5.f)
		{
			m_bAmp = false;
			CGameObject_Manager::Get_Instance()->Set_Dead();
			m_fAmptime = 0.f;
			m_iAmp_Count = 0;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
		}

	}
}

void CPlayer::SKill_WARLOCK()
{
	

}

void CPlayer::Skul_Change()
{

	
}

void CPlayer::Rect_Attack(P_STATE _State)
{
	if (m_State == P_ATTACK_1 || m_State == P_ATTACK_2)
	{
		if (m_bDirCheck == true)
		{
			m_Attack_Rect.left = (LONG)(m_tInfo.vPos.x) + 25;
			m_Attack_Rect.top = (LONG)(m_tInfo.vPos.y) - 20;
			m_Attack_Rect.right = (LONG)(m_tInfo.vPos.x) + 35;
			m_Attack_Rect.bottom = (LONG)(m_tInfo.vPos.y) + 20;
		}
		else
		{
			m_Attack_Rect.left = (LONG)(m_tInfo.vPos.x) - 35;
			m_Attack_Rect.top = (LONG)(m_tInfo.vPos.y) - 20;
			m_Attack_Rect.right = (LONG)(m_tInfo.vPos.x) - 25;
			m_Attack_Rect.bottom = (LONG)(m_tInfo.vPos.y) + 20;
		}
	}
	else if (m_Skul_State == SKUL_GUARD && m_State == P_SKILL_1
		 || m_State == P_SKILL_1_2 || m_State == P_SKILL_1_3)
	{
		if (m_bDirCheck == true)
		{
			m_Attack_Rect.left = (LONG)(m_tInfo.vPos.x) + 25;
			m_Attack_Rect.top = (LONG)(m_tInfo.vPos.y) - 20;
			m_Attack_Rect.right = (LONG)(m_tInfo.vPos.x) + 35;
			m_Attack_Rect.bottom = (LONG)(m_tInfo.vPos.y) + 20;
		}
		else
		{
			m_Attack_Rect.left = (LONG)(m_tInfo.vPos.x) - 35;
			m_Attack_Rect.top = (LONG)(m_tInfo.vPos.y) - 20;
			m_Attack_Rect.right = (LONG)(m_tInfo.vPos.x) - 25;
			m_Attack_Rect.bottom = (LONG)(m_tInfo.vPos.y) + 20;
		}
	}
	else
		m_Attack_Rect = { 0,0,0,0 };



}

void CPlayer::Hit()
{
	m_fHitTime += CTime_Manager::Get_Instance()->Get_TimeDelta();

	if (m_bHit == true)
	{
		if (rand() % 2 == 0)
			m_iA = 0;
		else m_iA = 255;
	}

	if (m_fHitTime >= 2)
	{
		m_fHitTime = 0.f;
		m_iA = 255;
		m_bHit = false;
	}

}






HRESULT CPlayer::Ready_GameObject()
{
	
	m_tInfo.vSize = { 1.f,1.f,0.f };
	m_tInfo.iAttack = 15.f;
	m_tInfo.iHp = 20000.f;
	m_tInfo.iMaxHp = 20000.f;
	m_tFrame = { 0.f,4.f };
	return S_OK;
}

int CPlayer::Update_GameObject()
{
	Update_Rect();
	OffSet();
	Dash();
	behavior();
	Skill_Pessive();
	Skill_Amp();
	Skul_Change();
	Rect_Attack(m_State);
	Hit();
	Combat();
	if (!m_bDash)
	{
		Jumping();
	}

	if (m_bPessive == true)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
		CSoundMgr::Get_Instance()->PlaySound(L"Happy.wav", CSoundMgr::PLAYER);
	}
	else if (m_bPessive == false)
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		CSoundMgr::Get_Instance()->PlaySound(L"Chapter1.wav", CSoundMgr::BGM);
	}
	
	if (CKey_Manager::Get_Instance()->Key_Down(KEY_TAP))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
		CSoundMgr::Get_Instance()->PlaySound(L"Chapter1.wav", CSoundMgr::BGM);
	}
	return 0;
}

void CPlayer::Late_Update_GameObject()
{
	if (m_Skul_State != SKUL_GUARD && m_State == P_ATTACK_1 || m_State == P_ATTACK_2)
		FrameMove(2.f);
	else if (m_Skul_State == SKUL_GUARD && m_State == P_SKILL_1 || m_State == P_SKILL_1_2 || m_State == P_SKILL_1_3)
		FrameMove(1.5f);
	else
		FrameMove(0.8f);

	if (m_Skul_State == SKUL_GUARD)
		EffectFrame(1.f);
	else
		EffectFrame(1.f);


	if (CKey_Manager::Get_Instance()->Key_Up(KEY_RIGHT))
	{
		m_State = P_STATE::P_IDLE;
		m_bDirCheck = true;
	}

	if (CKey_Manager::Get_Instance()->Key_Up(KEY_LEFT))
	{
		m_State = P_STATE::P_IDLE;
		m_bDirCheck = false;
	}


	/*if (GetAsyncKeyState(VK_RETURN))
	{
		CScene_Manager::Get_Instance()->Scene_Change_SceneManager(SCENEID::SCENE_STAGE);
	}*/
	

	if (GetAsyncKeyState('T'))
		m_tInfo.iHp -= 0.000000005;
}

void CPlayer::Render_GameObject()
{
	//오른쪽
	if (m_Skul_State == SKUL_NOMAL1)
	{
		if (m_bDirCheck == true)
		{
			Image(P_IDLE, L"Nomal_1", L"Idle", 3.f, true);
			Image(P_WALK, L"Nomal_1", L"Walk", 7.f, true);
			Image(P_ATTACK_1, L"Nomal_1", L"Attack_1", 4.f, true);
			Image(P_ATTACK_2, L"Nomal_1", L"Attack_2", 3.f, true);
			Image(P_JUMP, L"Nomal_1", L"Jump", 3.f, true);
			Image(P_FALL, L"Nomal_1", L"Fall", 1.f, true);
			Image(P_DASH, L"Nomal_1", L"Dash", 0.f, true);
			Image(P_SKILL_1, L"Nomal_1", L"Skill", 3.f, true);
			Image(P_SKILL_2, L"Nomal_1", L"Reborn_1", 8.f, true);
			Image(P_SKILL_2_2, L"Nomal_1", L"Reborn_2", 5.f, true);
			Image(P_JUMP_ATTACK, L"Nomal_1", L"JumpAttack", 3.f, true);
			Image(P_SWITCH, L"Nomal_1", L"Switch", 6.f, true);
			
		}
		//왼쪽
		else
		{
			Image(P_IDLE, L"Nomal_1", L"Idle", 3.f, false);
			Image(P_WALK, L"Nomal_1", L"Walk", 7.f, false);
			Image(P_ATTACK_1, L"Nomal_1", L"Attack_1", 4.f, false);
			Image(P_ATTACK_2, L"Nomal_1", L"Attack_2", 3.f, false);
			Image(P_JUMP, L"Nomal_1", L"Jump", 3.f, false);
			Image(P_FALL, L"Nomal_1", L"Fall", 1.f, false);
			Image(P_DASH, L"Nomal_1", L"Dash", 0.f, false);
			Image(P_SKILL_1, L"Nomal_1", L"Skill", 3.f, false);
			Image(P_SKILL_2, L"Nomal_1", L"Reborn_1", 8.f, false);
			Image(P_SKILL_2_2, L"Nomal_1", L"Reborn_2", 5.f, false);
			Image(P_JUMP_ATTACK, L"Nomal_1", L"JumpAttack", 3.f, false);
			Image(P_SWITCH, L"Nomal_1", L"Switch", 6.f, false);
		}
	}
	
	else if (m_Skul_State == SKUL_NOMAL2)
	{
		if (m_bDirCheck == true)
		{
			Image(P_IDLE, L"Nomal_2", L"Idle", 3.f, true);
			Image(P_WALK, L"Nomal_2", L"Walk", 7.f, true);
			Image(P_ATTACK_1, L"Nomal_2", L"Attack_1", 4.f, true);
			Image(P_ATTACK_2, L"Nomal_2", L"Attack_2", 3.f, true);
			Image(P_JUMP, L"Nomal_2", L"Jump", 1.f, true);
			Image(P_FALL, L"Nomal_2", L"Fall", 1.f, true);
			Image(P_DASH, L"Nomal_2", L"Dash", 0.f, true);
			Image(P_SKILL_1, L"Nomal_1", L"Skill", 3.f, true);
			Image(P_SKILL_2, L"Nomal_1", L"Reborn_1", 8.f, true);
			Image(P_SKILL_2_2, L"Nomal_1", L"Reborn_2", 5.f, true);

		}
		//왼쪽
		else
		{
			Image(P_IDLE, L"Nomal_2", L"Idle", 3.f, false);
			Image(P_WALK, L"Nomal_2", L"Walk", 7.f, false);
			Image(P_ATTACK_1, L"Nomal_2", L"Attack_1", 4.f, false);
			Image(P_ATTACK_2, L"Nomal_2", L"Attack_2", 3.f, false);
			Image(P_JUMP, L"Nomal_2", L"Jump", 1.f, false);
			Image(P_FALL, L"Nomal_2", L"Fall", 1.f, false);
			Image(P_DASH, L"Nomal_2", L"Dash", 0.f, false);
			Image(P_SKILL_1, L"Nomal_1", L"Skill", 3.f, false);
			Image(P_SKILL_2, L"Nomal_1", L"Reborn_1", 8.f, false);
			Image(P_SKILL_2_2, L"Nomal_1", L"Reborn_2", 5.f, false);
		}
	}

	else if (m_Skul_State == SKUL_ROCKSTAR)
	{
		if (m_bDirCheck == true)
		{
			Image(P_IDLE, L"RockStar", L"Idle", 5.f, true);
			Image(P_WALK, L"RockStar", L"Walk", 5.f, true);
			Image(P_ATTACK_1, L"RockStar", L"Attack_1", 7.f, true);
			Image(P_ATTACK_2, L"RockStar", L"Attack_2", 7.f, true);
			Image(P_DASH, L"RockStar", L"Dash", 3.f, true);
			Image(P_FALL, L"RockStar", L"Fall", 1.f, true);
			Image(P_JUMP, L"RockStar", L"Jump", 2.f, true);
			Image(P_JUMP_ATTACK, L"RockStar", L"JumpAttack", 3.f, true);
			Image(P_SKILL_1, L"RockStar", L"Skill_1", 3.f, true);
			Image(P_SWITCH, L"RockStar", L"Swtich", 2.f, true);
			Image_Effect(E_ATTACK, L"RockStar", L"Attack_Effect", 9.f, true, 35);
			
		}
		else
		{
			Image(P_IDLE, L"RockStar", L"Idle", 5.f, false);
			Image(P_WALK, L"RockStar", L"Walk", 5.f, false);
			Image(P_ATTACK_1, L"RockStar", L"Attack_1", 7.f, false);
			Image(P_ATTACK_2, L"RockStar", L"Attack_2", 7.f, false);
			Image(P_DASH, L"RockStar", L"Dash", 3.f, false);
			Image(P_FALL, L"RockStar", L"Fall", 1.f, false);
			Image(P_JUMP, L"RockStar", L"Jump", 2.f, false);
			Image(P_JUMP_ATTACK, L"RockStar", L"JumpAttack", 3.f, false);
			Image(P_SKILL_1, L"RockStar", L"Skill_1", 3.f, false);
			Image(P_SWITCH, L"RockStar", L"Swtich", 2.f, false);
			Image_Effect(E_ATTACK, L"RockStar", L"Attack_Effect", 9.f, false, 35);
		}
	}
	else if (m_Skul_State == SKUL_GUARD)
	{
		if (m_bDirCheck == true)
		{
			Image(P_IDLE, L"Guard", L"Idle", 5.f, true);
			Image(P_WALK, L"Guard", L"Walk", 5.f, true);
			Image(P_ATTACK_1, L"Guard", L"Attack_1", 9.f, true);
			Image(P_ATTACK_2, L"Guard", L"Attack_2", 5.f, true);
			Image(P_DASH, L"Guard", L"Dash", 4.f, true);
			Image(P_FALL, L"Guard", L"Fall", 1.f, true);
			Image(P_JUMP, L"Guard", L"Jump", 2.f, true);
			Image(P_JUMP_ATTACK, L"Guard", L"JumpAttack", 4.f, true);
			Image(P_SKILL_1, L"Guard", L"Skill1_1", 9.f, true);
			Image(P_SKILL_1_2, L"Guard", L"Skill1_2", 9.f, true);
			Image(P_SKILL_1_3, L"Guard", L"Skill1_3", 1.f, true);
			Image(P_SKILL_2, L"Guard", L"Skill_2", 7.f, true);
			Image_Effect(E_SKILL2_1, L"Guard", L"FireSlash_1", 9.f, true);
			Image_Effect(E_SKILL2_2, L"Guard", L"FireSlash_2", 9.f, true);
			Image(P_SWITCH, L"Guard", L"Switch", 8.f, true);
		}
		else
		{
			Image(P_IDLE, L"Guard", L"Idle", 5.f, false);
			Image(P_WALK, L"Guard", L"Walk", 5.f, false);
			Image(P_ATTACK_1, L"Guard", L"Attack_1", 9.f, false);
			Image(P_ATTACK_2, L"Guard", L"Attack_2", 5.f, false);
			Image(P_DASH, L"Guard", L"Dash", 4.f, false);
			Image(P_FALL, L"Guard", L"Fall", 1.f, false);
			Image(P_JUMP, L"Guard", L"Jump", 2.f, false);
			Image(P_JUMP_ATTACK, L"Guard", L"JumpAttack", 4.f, false);
			Image(P_SKILL_1, L"Guard", L"Skill1_1", 9.f, false);
			Image(P_SKILL_1_2, L"Guard", L"Skill1_2", 9.f, false);
			Image(P_SKILL_1_3, L"Guard", L"Skill1_3", 1.f, false);
			Image(P_SKILL_2, L"Guard", L"Skill_2", 7.f, false);
			Image(P_SKILL_2, L"Guard", L"FireSlash_1", 9.f, false);
			Image(P_SKILL_2, L"Guard", L"FireSlash_2", 9.f, false);
			Image(P_SWITCH, L"Guard", L"Switch", 8.f, false);
		}
	}
	else if (m_Skul_State == SKUL_WARLOCK)
	{
		if (m_bDirCheck == true)
		{
			
			Image(P_IDLE, L"Warlock", L"Idle", 5.f, true, 10.f);
			Image(P_WALK, L"Warlock", L"Walk", 5.f, true, 10.f);
			Image(P_ATTACK_1, L"Warlock", L"Attack_1", 6.f, true, 10.f);
			Image(P_ATTACK_2, L"Warlock", L"Attack_2", 3.f, true, 10.f);
			Image(P_DASH, L"Warlock", L"Dash", 1.f, true, 10.f);
			Image(P_FALL, L"Warlock", L"Fall", 1.f, true, 10.f);
			Image(P_JUMP, L"Warlock", L"Jump", 2.f, true, 10.f);
			Image(P_JUMP_ATTACK, L"Warlock", L"JumpAttack", 6.f, true, 10.f);
			Image(P_SKILL_1_CHARGE, L"Warlock", L"Skill1_Charge", 2.f, true, 10.f);
			Image_Effect(E_SKILL_1, L"Warlock", L"Skill1_Charge_1", 9.f, true);
			Image_Effect(E_SKILL_2, L"Warlock", L"Skill1_Charge_2", 9.f, true);
			Image_Effect(E_SKILL_3, L"Warlock", L"Skill1_Charge_3", 4.f, true);
			Image(P_SKILL_1_CHARGE_COMPLETED, L"Warlock", L"Skill1_completed", 9.f, true, 10.f);
			Image(P_SKILL_2_CHARGE, L"Warlock", L"Skill2_Charge", 2.f, true, 10.f);
			Image_Effect(E_SKILL2_1, L"Warlock", L"Skill2_Charge_1", 9.f, true);
			Image_Effect(E_SKILL2_2, L"Warlock", L"Skill2_Charge_2", 9.f, true);
			Image_Effect(E_SKILL2_3, L"Warlock", L"Skill2_Charge_3", 3.f, true);
			Image(P_SKILL_2_CHARGE_COMPLETED, L"Warlock", L"Skill2_Completed", 9.f, true, 10.f);
			Image_Effect(E_SKILL_SWITCH, L"Warlock", L"Switch", 9.f, true);
		}
		else
		{
			Image(P_IDLE, L"Warlock", L"Idle", 5.f, false, 10.f);
			Image(P_WALK, L"Warlock", L"Walk", 5.f, false, 10.f);
			Image(P_ATTACK_1, L"Warlock", L"Attack_1", 6.f, false, 10.f);
			Image(P_ATTACK_2, L"Warlock", L"Attack_2", 3.f, false, 10.f);
			Image(P_DASH, L"Warlock", L"Dash", 1.f, false, 10.f);
			Image(P_FALL, L"Warlock", L"Fall", 1.f, false, 10.f);
			Image(P_JUMP, L"Warlock", L"Jump", 2.f, false, 10.f);
			Image(P_JUMP_ATTACK, L"Warlock", L"JumpAttack", 6.f, false, 10.f);
			Image(P_SKILL_1_CHARGE, L"Warlock", L"Skill1_Charge", 2.f, false, 10.f);
			Image_Effect(E_SKILL_1, L"Warlock", L"Skill1_Charge_1", 9.f, false);
			Image_Effect(E_SKILL_2, L"Warlock", L"Skill1_Charge_2", 9.f, false);
			Image_Effect(E_SKILL_3, L"Warlock", L"Skill1_Charge_3", 4.f, false);
			Image(P_SKILL_1_CHARGE_COMPLETED, L"Warlock", L"Skill1_completed", 9.f, false, 10.f);
			Image(P_SKILL_2_CHARGE, L"Warlock", L"Skill2_Charge", 2.f, false, 10.f);
			Image_Effect(E_SKILL2_1, L"Warlock", L"Skill2_Charge_1", 9.f, false);
			Image_Effect(E_SKILL2_2, L"Warlock", L"Skill2_Charge_2", 9.f, false);
			Image_Effect(E_SKILL2_3, L"Warlock", L"Skill2_Charge_3", 3.f, false);
			Image(P_SKILL_2_CHARGE_COMPLETED, L"Warlock", L"Skill2_Completed", 9.f, false, 10.f);
			Image_Effect(E_SKILL_SWITCH, L"Warlock", L"Switch", 9.f, false);
		}
	}


	if (m_State == P_DASH)
	{
		m_Effect = E_DASH;
		if(m_bDirCheck== true)
			Image_Effect(E_DASH, L"Dash_Smoke", L"Dash", 9.f, true, -40.f, 0.f);
		else
			Image_Effect(E_DASH, L"Dash_Smoke", L"Dash", 9.f, false, -40.f, 0.f);
	}

	if (m_State == P_JUMP)
	{
		m_Effect = E_JUMP;
		Image_Effect(E_JUMP, L"Double_Smoke", L"jump", 9.f, true,0.f,20.f);
	}
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		_vec2 vecArray[5];
		int iX = (int)CScroll_Manager::Get_Scroll().x;
		vecArray[0] = { (float)m_tRect.left - iX, (float)m_tRect.top };
		vecArray[1] = { (float)m_tRect.right - iX,(float)m_tRect.top };
		vecArray[2] = { (float)m_tRect.right - iX,(float)m_tRect.bottom };
		vecArray[3] = { (float)m_tRect.left - iX,(float)m_tRect.bottom };
		vecArray[4] = { (float)m_tRect.left - iX,(float)m_tRect.top };


		D3DSPRITE->End();


		D3DLINE->Draw(vecArray, 5, D3DCOLOR_ARGB(255, 255, 0, 255));
		D3DSPRITE->Begin(D3DXSPRITE_ALPHABLEND);
	}
}

void CPlayer::Relaese_GameObject()
{

}







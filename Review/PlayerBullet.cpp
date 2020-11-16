#include "stdafx.h"
#include "PlayerBullet.h"
#include "Player.h"
#include "GameObject_Manager.h"
#include "Line_Manager.h"
#include "Scroll_Manager.h"
#include "SoundMgr.h"

CPlayerBullet::CPlayerBullet()
	: m_fAngle(0.f), m_fFallTime(0)
{
	m_vPlayer = CGameObject_Manager::Get_Instance()->Get_Player_Pos();
	
	m_fTemp = m_tInfo.vPos.x;
	m_bDead = false;
	m_bFall = false;
}


CPlayerBullet::~CPlayerBullet()
{
}

HRESULT CPlayerBullet::Ready_GameObject()
{
	m_tInfo.vSize = { 1.f,1.f,0.f };

	if (m_Skul_State == SKUL_NOMAL1)
		m_tInfo.iAttack = 10;
	else if (m_Skul_State == SKUL_ROCKSTAR)
		m_tInfo.iAttack = 20;
	else if (m_Skul_State == SKUL_GUARD)
		m_tInfo.iAttack = 30;
	else if (m_Skul_State == SKUL_WARLOCK && m_Effect == E_SKILL_IDLE)
		m_tInfo.iAttack = 15;
	else if (m_Skul_State == SKUL_WARLOCK && m_Effect == E_SKILL_1)
		m_tInfo.iAttack = 30;
	else if (m_Skul_State == SKUL_WARLOCK && m_Effect == E_SKILL_2)
		m_tInfo.iAttack = 50;
	return S_OK;
}

int CPlayerBullet::Update_GameObject()
{
	if (m_bDead && m_Skul_State != SKUL_NOMAL1 || m_Skul_State == SKUL_NOMAL2)
		return OBJ_DEAD;

	if (m_Skul_State == SKUL_ROCKSTAR)
	{
		FrameMove(3.f);
		EffetFrame(3.f);
	}
	if (m_Skul_State == SKUL_NOMAL1)
	{
		float fy;
		bool bLineCol = CLine_Manager::Get_Instance()->CollisionLine(m_tInfo.vPos.x, &fy);
		
		if (bLineCol && fy -2.f < m_tInfo.vPos.y)
		{

			m_tInfo.vPos.y = fy;
		}

		float fx = m_vPlayer.x - m_tInfo.vPos.x;

		if (m_bFall == false)
		{
			if (m_bDir == true && m_fSpeed != 0)
			{
				m_fSpeed = 10.f;
				m_tInfo.vPos.x += m_fSpeed;
				m_fAngle += 30.f;

				if (fx < -300)
				{
					m_fSpeed = 0.f;
				}
			}
			else if (m_bDir == false && m_fSpeed != 0)
			{
				m_fSpeed = 10.f;
				m_tInfo.vPos.x -= m_fSpeed;
				m_fAngle -= 30.f;
				if (fx > 300)
				{
					m_fSpeed = 0.f;
					m_bDead = true;

				}
			}
			if (m_fSpeed == 0)
				m_tInfo.vPos.y += 5.f;
		}
		else if (m_bFall == true)
		{
			m_tInfo.vPos.y += 5.f;
		}
	}

	if (m_Skul_State == SKUL_GUARD)
	{
		if (m_bDir == true)
		{
			m_tInfo.vPos.x += 10.f;
		}
		else if (m_bDir == false)
		{
			m_tInfo.vPos.x -= 10.f;
		}
		FrameMove(1.f);
	}
	if (m_Skul_State == SKUL_WARLOCK)
	{
		float fx = m_vPlayer.x - m_tInfo.vPos.x;
		if (m_Effect == E_SKILL_1)
		{
			if (m_bDir == true && m_fSpeed != 0.f)
			{
				m_fSpeed = 2.f;
				m_tInfo.vPos.x += m_fSpeed;
				if (fx < -250)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"HighWarlock_Orb_completed_Roof.wav", CSoundMgr::EFFECT);
					m_fSpeed = 0.f;
					m_Effect = E_SKILL_1_END;
				}
			}
			else if (m_bDir == false)
			{
				m_fSpeed = 2.f;
				m_tInfo.vPos.x -= m_fSpeed;
				if (fx > 250)
				{
					CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
					CSoundMgr::Get_Instance()->PlaySound(L"HighWarlock_Orb_completed_Roof.wav", CSoundMgr::EFFECT);
					m_fSpeed = 0.f;
					m_Effect = E_SKILL_1_END;
				}
				
			}
		}
		else if (m_Effect == E_SKILL2_1)
		{	
			m_fFallTime += 0.05f;
			m_tInfo.vPos.y += 1.f + m_fFallTime;


			if (m_vPlayer.y <= m_tInfo.vPos.y + 40.f)
			{
				m_Effect = E_SKILL_2_END;
				m_tInfo.iAttack = 50;
				m_tRect.left = (LONG)(m_tInfo.vPos.x) - 400;
				m_tRect.top = (LONG)(m_tInfo.vPos.y) - 420;
				m_tRect.right = (LONG)(m_tInfo.vPos.x) + 400;
				m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 420;
				CScroll_Manager::Get_Instance()->On_Shake();
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::EFFECT);
				CSoundMgr::Get_Instance()->PlaySound(L"HighWarlock_Meteor_roof (mp3cut.net).wav", CSoundMgr::EFFECT);

				
			}
		}
		else if (m_Effect == E_SKILL_IDLE)
		{
			if (m_bDir == true)
				m_tInfo.vPos.x += 5.f;
			else
				m_tInfo.vPos.x -= 5.f;
		}

		FrameMove(1.f);
	}
	else
		FrameMove(1.f);

	Ready_Rect();
	return 0;
}

void CPlayerBullet::Late_Update_GameObject()
{
	if (m_tInfo.vPos.x >= WINCX || m_tInfo.vPos.x <= 0)
	{
		m_bDead = true;
	}
}

void CPlayerBullet::Render_GameObject()
{



	if (m_Skul_State == SKUL_NOMAL1)
	{
		if (m_bDir == true)
			Image(L"Nomal_1", L"Head", 0.f, true);

		else if (m_bDir == false)
			Image(L"Nomal_1", L"Head", 0.f, false);
	}
	else if (m_Skul_State == SKUL_ROCKSTAR)
	{
		Image_Effect(L"RockStar", L"AmpEffect_1", 5.f);
		Image_Effect(L"RockStar", L"AmpEffect_2", 5.f);
		Image(L"RockStar", L"Amp", 0.f, true);
	}
	else if (m_Skul_State == SKUL_GUARD)
	{
		if(m_bDir == true)
			Image(L"Guard", L"Fireball", 8.f, true);
		else
			Image(L"Guard", L"Fireball", 8.f, false);
	}
	else if (m_Skul_State == SKUL_WARLOCK)
	{
		if(m_Effect == E_SKILL_1)
			Image(L"Warlock", L"Skill1_completed_2", 9.f,true);
		else if(m_Effect == E_SKILL2_1)
			Image_Warlock(L"Warlock", L"Skill2_completed_1", 7.f, true);
		else if(m_Effect == E_SKILL_1_END)
			Image(L"Warlock", L"Skill1_Effect", 9.f, true);
		else if(m_Effect == E_SKILL_2_END)
			Image(L"Warlock", L"Skill2_Effect_1", 9.f, true);
		else if (m_Effect == E_SKILL_2_END_2)
			Image(L"Warlock", L"Skill2_Effect_2", 9.f, true);
		else if (m_Effect == E_SKILL_2_END_3)
			Image(L"Warlock", L"Skill2_Effect_3", 9.f, true);

		if(m_bDir == true && m_Effect == E_SKILL_IDLE)
			Image(L"Warlock", L"BasicAttack", 9.f, true, 5.f);
		else if(m_bDir == false && m_Effect == E_SKILL_IDLE)
			Image(L"Warlock", L"BasicAttack", 9.f, false, 5.f);
		
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

void CPlayerBullet::Relaese_GameObject()
{
}

void CPlayerBullet::Image(const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame, bool _dir, float _y)
{
	if (_dir == true)
	{
		m_tFrame.fEndFrame = EndFrame;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		_matrix matScale, matRotation , matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - _y), 0.f);

		matWolrd = matScale* matRotation * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
	else
	{
		m_tFrame.fEndFrame = EndFrame;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		_matrix matScale, matRotation,matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y) - _y), 0.f);

		matWolrd = matScale*matRotation * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	if (m_Effect == E_SKILL_2_END || m_Effect == E_SKILL_2_END_2 || m_Effect == E_SKILL_2_END_3)
	{
		m_tFrame.fEndFrame = EndFrame;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		_matrix matScale, matRotation, matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, 4.f, 4.f, 0.f);
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(m_fAngle));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), (m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y)) - 50.f , 0.f);

		matWolrd = matScale*matRotation * matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CPlayerBullet::Image_Effect(const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame)
{
	m_Effect_Frame.fEndFrame = EndFrame;
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_Effect_Frame.fStartFrame));
	if (nullptr == pTexInfo)
		return;
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	_matrix matScale, matRotation, matTrans, matWolrd;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(m_fAngle));
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

	matWolrd = matScale* matRotation * matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayerBullet::Image_Warlock(const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame, bool _dir)
{
	if (_dir == true)
	{
		m_tFrame.fEndFrame = EndFrame;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		_matrix matScale, matRotation, matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(90.f));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

		matWolrd = matScale* matRotation*matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
	else
	{
		m_tFrame.fEndFrame = EndFrame;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		_matrix matScale, matRotation, matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixRotationZ(&matRotation, D3DXToRadian(90.f));
		D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

		matWolrd = matScale*matRotation *matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CPlayerBullet::FrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	

	if (m_Effect == E_SKILL_1_END && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f;
		Dead_Rect();
	
		m_Effect = E_SKILL_END;
	}
	
	if (m_Effect == E_SKILL_2_END && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f;
		m_Effect = E_SKILL_2_END_2;

	}
	else if (m_Effect == E_SKILL_2_END_2 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f;
		m_Effect = E_SKILL_2_END_3;
	
	}
	else if (m_Effect == E_SKILL_2_END_3 && m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f;
		
		m_Effect = E_SKILL_END;
		Dead_Rect();
		m_tInfo.iAttack = 30;
	}

	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f;
	}

}

void CPlayerBullet::EffetFrame(float fSpeed)
{
	m_Effect_Frame.fStartFrame += m_Effect_Frame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;

	if (m_Effect_Frame.fStartFrame > m_Effect_Frame.fEndFrame)
	{
		m_Effect_Frame.fStartFrame = 0.f;

	}
}

void CPlayerBullet::Fall_Skul()
{
	m_tInfo.vPos.y += 5.f;
}

void CPlayerBullet::Dead_Rect()
{
	m_tRect = { 0,0,0,0 };
}

void CPlayerBullet::Ready_Rect()
{
	if (m_Skul_State == SKUL_NOMAL1 || m_Skul_State == SKUL_NOMAL2 )
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) - 10;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 10;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 10;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 10;
	}
	else if (m_Skul_State == SKUL_ROCKSTAR)
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) - 70;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 70;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 70;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 70;
	}
	else if (m_Skul_State == SKUL_GUARD)
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) -30;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 25;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 30;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 25;
	}
	else if (m_Skul_State == SKUL_WARLOCK && m_Effect == E_SKILL_1)
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) - 60;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 60;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 60;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 60;
	}
	else if (m_Skul_State == SKUL_WARLOCK && m_Effect == E_SKILL2_1)
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) - 100;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 120;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 100;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 120;
	}
	else if (m_Skul_State == SKUL_WARLOCK && m_Effect == E_SKILL_IDLE)
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) - 20;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 15;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 20;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 10;
	}
}

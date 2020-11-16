#include "stdafx.h"
#include "Pessive.h"
#include "GameObject_Manager.h"
#include "Time_Manager.h"

CPessive::CPessive()
	:m_fTime(0)
{
	m_tInfo.iAttack = 7.f;
	m_Skul_State = SKUL_ROCKSTAR;
}


CPessive::~CPessive()
{
}

HRESULT CPessive::Ready_GameObject()
{
	
	m_tInfo.vSize = { 1.f,1.f,0.f };
	return S_OK;
}

int CPessive::Update_GameObject()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_fTime += CTime_Manager::Get_Instance()->Get_TimeDelta();
	if (m_fTime >= 7.f)
	{
		FrameMove(10.f);
		m_tInfo.iAttack = 30.f;
	}
	else if (m_fTime >= 4 && m_fTime < 6)
	{
		FrameMove(7.f);
		m_tInfo.iAttack = 20.f;
	}
	else
	{
		FrameMove(5.f);
		m_tInfo.iAttack = 10.f;
	}



	Ready_Rect();
	return 0;
}

void CPessive::Late_Update_GameObject()
{
}

void CPessive::Render_GameObject()
{
	Image(L"RockStar", L"Pessive", 2.f);
	Image_Spark(L"RockStar", L"Spark", 3.f, m_tInfo.vPos.x + 150.f, m_tInfo.vPos.y - 65.f, true);
	Image_Spark(L"RockStar", L"Spark", 3.f, m_tInfo.vPos.x - 150.f, m_tInfo.vPos.y - 65.f, false);

	
	if(m_fTime > 3.f)
	{
		Image_Spark2(L"RockStar", L"Spark", 3.f, m_tInfo.vPos.x + 170.f, m_tInfo.vPos.y - 55.f, true);
		Image_Spark2(L"RockStar", L"Spark", 3.f, m_tInfo.vPos.x - 170.f, m_tInfo.vPos.y - 55.f, false);
		
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

void CPessive::Relaese_GameObject()
{

}

void CPessive::Image(const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame)
{
	m_tFrame.fEndFrame = EndFrame;
	const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
	if (nullptr == pTexInfo)
		return;
	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

	_matrix matScale, matTrans, matWolrd;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), m_tInfo.vPos.y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

	matWolrd = matScale* matTrans;

	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
	CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPessive::Image_Spark(const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame, float _x, float _y, bool _Dir)
{
	if (_Dir == true)
	{
		m_tFrame.fEndFrame = EndFrame;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		_matrix matScale, matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, _x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), _y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

		matWolrd = matScale* matTrans;

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

		_matrix matScale, matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, _x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), _y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

		matWolrd = matScale* matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CPessive::Image_Spark2(const wstring & wstrObjectKey, const wstring & wstrStateKey, float EndFrame, float _x, float _y, bool _Dir)
{
	if (_Dir == true)
	{
		m_tFrame.fEndFrame = EndFrame;
		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(wstrObjectKey, wstrStateKey, DWORD(m_tFrame.fStartFrame));
		if (nullptr == pTexInfo)
			return;
		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);

		_matrix matScale, matTrans,matRotation,matWolrd;
		D3DXMatrixScaling(&matScale, m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, _x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), _y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

		matWolrd = matScale *matTrans;

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

		_matrix matScale, matTrans, matWolrd;
		D3DXMatrixScaling(&matScale, -m_tInfo.vSize.x, m_tInfo.vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, _x - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_X), _y - CScroll_Manager::Get_Scroll(CScroll_Manager::SCROLL_Y), 0.f);

		matWolrd = matScale* matTrans;

		CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matWolrd);
		CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CPessive::FrameMove(float fSpeed)
{
	m_tFrame.fStartFrame += m_tFrame.fEndFrame * CTime_Manager::Get_Instance()->Get_TimeDelta() * fSpeed;
	if (m_tFrame.fStartFrame > m_tFrame.fEndFrame)
	{
		m_tFrame.fStartFrame = 0.f;

	}
}

void CPessive::Ready_Rect()
{
	if (m_fTime > 3.f)
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) - 400;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 400;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 400;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 400;
	}
	else
	{
		m_tRect.left = (LONG)(m_tInfo.vPos.x) - 100;
		m_tRect.top = (LONG)(m_tInfo.vPos.y) - 100;
		m_tRect.right = (LONG)(m_tInfo.vPos.x) + 100;
		m_tRect.bottom = (LONG)(m_tInfo.vPos.y) + 100;
	}
}



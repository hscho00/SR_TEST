#include "stdafx.h"
#include "FrameManager.h"
#include "TimeManager.h"
#include "Graphic_Device.h"


CFrameManager::CFrameManager()
	: m_CPUTick(), m_startTime(), m_endTime(), m_fSPF(0.f), m_fInitTime(0.f), m_iFPS(0), m_fFPSTime(0.f), m_szFPS(_T(""))
{

}

CFrameManager* CFrameManager::Create(float fFPS)
{
	CFrameManager* pInstance = new CFrameManager;
	pInstance->Ready_FrameManager(fFPS);
	return pInstance;
}

HRESULT CFrameManager::Ready_FrameManager(float fFPS)
{
	m_fSPF = 1.f / fFPS;
	QueryPerformanceFrequency(&m_CPUTick);
	QueryPerformanceCounter(&m_startTime);
	QueryPerformanceCounter(&m_endTime);

	return S_OK;
}

bool CFrameManager::LockFrame()
{
	QueryPerformanceFrequency(&m_CPUTick);
	QueryPerformanceCounter(&m_endTime);

	float deltaTime = float(m_endTime.QuadPart - m_startTime.QuadPart) / m_CPUTick.QuadPart;
	m_fInitTime += deltaTime;
	m_startTime.QuadPart = m_endTime.QuadPart;

	if (m_fInitTime > m_fSPF)
	{
		++m_iFPS;
		m_fInitTime = 0.f;
		return true;
	}

	return false;
}

void CFrameManager::RenderFPS()
{
	m_fFPSTime += CTimeManager::Get_Instance()->Get_DeltaTime();

	if (m_fFPSTime > 1.f)
	{ 
		swprintf_s(m_szFPS, _T("FPS : %d"), m_iFPS);
		m_iFPS = 0;
		m_fFPSTime = 0.f;
	}
	
	_matrix matTrans;
	D3DXMatrixTranslation(&matTrans, 10.f, 10.f, 0.f);
	CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&matTrans);
	CGraphic_Device::Get_Instance()->Get_Font()->DrawText(CGraphic_Device::Get_Instance()->Get_Sprite(), 
		m_szFPS, _tcslen(m_szFPS), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
}

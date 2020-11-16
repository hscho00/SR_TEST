#include "stdafx.h"
#include "TimeManager.h"

IMPLEMENT_SINGLETON(CTimeManager)

CTimeManager::CTimeManager()
	: m_CPUTick(), m_startTime(), m_endTime(), m_fDeltaTime(0.f), m_fInitTime(0.f)
{

}

HRESULT CTimeManager::Ready_TimeMgr()
{
	QueryPerformanceFrequency(&m_CPUTick);
	QueryPerformanceCounter(&m_startTime);
	QueryPerformanceCounter(&m_endTime);
	m_fDeltaTime = 0.f;

	return S_OK;
}

void CTimeManager::Compute_TimeMgr()
{
	QueryPerformanceCounter(&m_endTime);
	
	m_fDeltaTime = float(m_endTime.QuadPart - m_startTime.QuadPart) / m_CPUTick.QuadPart;
	m_startTime.QuadPart = m_endTime.QuadPart;

	m_fInitTime += m_fDeltaTime;
	if (m_fInitTime > 1.f)
	{
		QueryPerformanceFrequency(&m_CPUTick);
		m_fInitTime = 0.f;
	}
}

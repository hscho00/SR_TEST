#include "..\Headers\TimeManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CTimeManager)

CTimeManager::CTimeManager()
	: m_CPUTick(), m_startTime(), m_endTime(), m_fInitCPUTickTime(0.f), m_fDeltaTime(0.f)
{

}

HRESULT CTimeManager::ReadyTimeManager()
{
	QueryPerformanceFrequency(&m_CPUTick);
	QueryPerformanceCounter(&m_startTime);
	QueryPerformanceCounter(&m_endTime);

	return S_OK;
}

void CTimeManager::UpdateTimeManager()
{
	QueryPerformanceCounter(&m_endTime);

	m_fDeltaTime = float(m_endTime.QuadPart - m_startTime.QuadPart) / m_CPUTick.QuadPart;
	m_startTime.QuadPart = m_endTime.QuadPart;

	m_fInitCPUTickTime += m_fDeltaTime;
	if (m_fInitCPUTickTime > 1.f)
	{
		QueryPerformanceFrequency(&m_CPUTick);
		m_fInitCPUTickTime = 0.f;
	}
}

void CTimeManager::Free()
{

}
#include "..\Headers\TimeManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(TimeManager)

TimeManager::TimeManager()
	: m_fInitCPUTickTime(0.f), m_fDeltaTime(0.f)
{
	ZeroMemory(&m_CpuCount, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_StartTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_GoalTime, sizeof(LARGE_INTEGER));
}

void TimeManager::ReadyTimeManager()
{
	QueryPerformanceCounter(&m_StartTime);
	QueryPerformanceCounter(&m_GoalTime);
	QueryPerformanceFrequency(&m_CpuCount);
}

DOUBLE TimeManager::UpdateTimeManager()
{
	QueryPerformanceFrequency(&m_CpuCount);
	m_fDeltaTime = float(m_GoalTime.QuadPart - m_StartTime.QuadPart) / m_CpuCount.QuadPart;
	m_StartTime.QuadPart = m_GoalTime.QuadPart;

	m_fInitCPUTickTime += m_fDeltaTime;
	if (m_fInitCPUTickTime > 1.f)
	{
		QueryPerformanceFrequency(&m_CpuCount);
		m_fInitCPUTickTime = 0.f;
	}
	return m_fDeltaTime;
}

void TimeManager::Free()
{

}

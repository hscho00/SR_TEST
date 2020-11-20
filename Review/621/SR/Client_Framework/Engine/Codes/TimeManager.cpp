#include "..\Headers\TimeManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(TimeManager)

TimeManager::TimeManager()
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
	QueryPerformanceCounter(&m_GoalTime);
	DOUBLE fDeltaTime = float(m_GoalTime.QuadPart - m_StartTime.QuadPart);
	m_StartTime.QuadPart = m_GoalTime.QuadPart;
	return fDeltaTime;
}

void TimeManager::Free()
{

}

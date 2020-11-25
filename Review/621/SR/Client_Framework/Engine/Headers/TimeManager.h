#pragma once
#ifndef __TIME_MANAGER_H__
#define __TIME_MANAGER_H__

#include "Base.h"

CODEBEGIN(Engine)
class TimeManager final : public CBase
{
	DECLARE_SINGLETON(TimeManager)
private:
	TimeManager();
	virtual ~TimeManager() = default;

public:
	void	ReadyTimeManager();
	DOUBLE	UpdateTimeManager();

public:
	virtual void Free() override;

public:
	float Get_DeltaTime() const { return m_fDeltaTime; }

private:
	LARGE_INTEGER m_CpuCount;
	LARGE_INTEGER m_StartTime;
	LARGE_INTEGER m_GoalTime;

	float m_fInitCPUTickTime;
	float m_fDeltaTime;
};
CODEEND
#endif
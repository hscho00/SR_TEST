#pragma once
#ifndef __TIMEMANAGER_H__

#include "Base.h"

BEGIN(Engine)
class CTimeManager final : public CBase
{
	DECLARE_SINGLETON(CTimeManager)

private:
	CTimeManager();
	virtual ~CTimeManager() = default;

public:
	HRESULT ReadyTimeManager();
	void	UpdateTimeManager();

	float Get_DeltaTime() const { return m_fDeltaTime; }

public:
	virtual void Free() override;

private:
	LARGE_INTEGER m_CPUTick;
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_endTime;

	float m_fInitCPUTickTime;
	
	float m_fDeltaTime;

};
END

#define __TIMEMANAGER_H__
#endif
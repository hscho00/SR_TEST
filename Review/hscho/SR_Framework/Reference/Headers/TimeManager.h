#pragma once
#ifndef __TIMEMANAGER_H__

#include "Base.h"

BEGIN(Engine)
class CTimeManager : public CBase
{
	DECLARE_SINGLETON(CTimeManager)

private:
	CTimeManager();
	virtual ~CTimeManager() = default;

public:
	HRESULT Ready_TimeMgr();
	void	Compute_TimeMgr();

	float Get_DeltaTime() const { return m_fDeltaTime; }

public:
	virtual void Free() override;

private:
	LARGE_INTEGER m_CPUTick;
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_endTime;

	float m_fDeltaTime;
	float m_fInitTime;

};
END

#define __TIMEMANAGER_H__
#endif
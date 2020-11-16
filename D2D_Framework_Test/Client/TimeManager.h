#pragma once
class CTimeManager
{
	DECLARE_SINGLETON(CTimeManager)

private:
	CTimeManager();
	~CTimeManager() = default;

public:
	float Get_DeltaTime() const { return m_fDeltaTime; }

public:
	HRESULT Ready_TimeMgr();
	void	Compute_TimeMgr();

private:
	LARGE_INTEGER m_CPUTick;
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_endTime;

	float m_fDeltaTime;
	float m_fInitTime;

};


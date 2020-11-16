#pragma once
class CFrameManager
{
private:
	CFrameManager();
public:
	~CFrameManager() = default;

public:
	static CFrameManager* Create(float fFPS);
	
	bool LockFrame();
	void RenderFPS();

private:
	HRESULT Ready_FrameManager(float fFPS);

private:
	LARGE_INTEGER m_CPUTick;
	LARGE_INTEGER m_startTime;
	LARGE_INTEGER m_endTime;

	float	m_fSPF;
	float	m_fInitTime;

	int		m_iFPS;
	float	m_fFPSTime;
	TCHAR	m_szFPS[64];

};


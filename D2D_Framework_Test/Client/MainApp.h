#pragma once

class CGraphic_Device;
class CTimeManager;
class CFrameManager;
class CKeyManager;
class CSceneManager;
class CObjManager;

class CMainApp
{
private:
	CMainApp();
public:
	virtual ~CMainApp() = default;

public:
	static CMainApp* Create();
	void Destroy();

public:
	HRESULT Ready_MainApp();
	void Update_MainApp(); 
	void LateUpdate_MainApp(); 
	void Render_MainApp(CFrameManager* pFrameManager); 

private:
	void Release_MainApp(); 

private:
	CGraphic_Device* m_pGraphic_Device;
	CTimeManager* m_pTimeManager;
	CKeyManager* m_pKeyManager;
	CSceneManager* m_pSceneManager;
	CObjManager* m_pObjManager;

};


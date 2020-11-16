#pragma once

class CScene;

class CSceneManager
{
	DECLARE_SINGLETON(CSceneManager)

private:
	CSceneManager();
	~CSceneManager();

public:
	void Update_SceneMgr();
	void LateUpdate_SceneMgr();
	void Render_SceneMgr();

private:
	void Release_SceneMgr();

public:
	CScene* Get_CurScene() { return m_pCurScene; }
	SCENE::ID Get_CurSceneID() const { return m_eCurScene; }
	HRESULT ChangeScene(SCENE::ID eNextScene);

private:
	SCENE::ID m_eCurScene;
	SCENE::ID m_eNextScene;

	CScene* m_pCurScene;

};


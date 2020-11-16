#include "stdafx.h"
#include "SceneManager.h"
#include "Stage1.h"

IMPLEMENT_SINGLETON(CSceneManager)

CSceneManager::CSceneManager()
	: m_eCurScene(SCENE::ID::END)
	, m_eNextScene(SCENE::ID::END)
	, m_pCurScene(nullptr)
{

}

CSceneManager::~CSceneManager()
{
	Release_SceneMgr();
}

void CSceneManager::Update_SceneMgr()
{
	m_pCurScene->Update_Scene();
}

void CSceneManager::LateUpdate_SceneMgr()
{
	m_pCurScene->LateUpdate_Scene();
}

void CSceneManager::Render_SceneMgr()
{
	m_pCurScene->Render_Scene();
}

void CSceneManager::Release_SceneMgr()
{
	Safe_Delete(m_pCurScene);
}

HRESULT CSceneManager::ChangeScene(SCENE::ID eNextScene)
{
	m_eNextScene = eNextScene;
	if (m_eCurScene != m_eNextScene)
	{
		Safe_Delete(m_pCurScene);

		switch (m_eNextScene)
		{
		case SCENE::ID::STAGE_1:
			m_pCurScene = new CStage1;
			m_pCurScene->Ready_Scene();
			break;
		default:
			return E_FAIL;
		}

		m_eCurScene = m_eNextScene;
	}

	return S_OK;
}

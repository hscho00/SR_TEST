#include "SceneManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(SceneManager)

SceneManager::SceneManager()
{
}

HRESULT SceneManager::SetUpCurrentScene(_int iSceneID, Scene* pCurrentScene)
{
	if (nullptr == pCurrentScene)
		return E_FAIL;

	if (m_iSceneID != iSceneID)
	{
		SafeRelease(m_pCurrentScene);
		m_pCurrentScene = pCurrentScene;

		m_iSceneID = iSceneID;
	}

	return S_OK;
}

_uint SceneManager::UpdateScene()
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->UpdateScene();
}

_uint SceneManager::LateUpdateScene()
{
	if (nullptr == m_pCurrentScene)
		return 0;

	return m_pCurrentScene->LateUpdateScene();
}

void SceneManager::Free()
{
	SafeRelease(m_pCurrentScene);
}

#include "..\Headers\SceneManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CSceneManager)

CSceneManager::CSceneManager()
	: m_pCurrentScene(nullptr)
{

}

HRESULT CSceneManager::SetUpCurrentScene(CScene* pNextScene)
{
	if (nullptr == pNextScene
		|| (pNextScene->Get_SceneIndex() == -1)) // m_iSceneIndex 꼭 지정해 주시오
	{
		SafeRelease(pNextScene);	// 밖에서 생성한 것을 넘겨주므로 받은건 release
									// m_pCurrentScene은 변화 X
		return E_FAIL;
	}

	if (nullptr == m_pCurrentScene)
	{
		m_pCurrentScene = pNextScene;
		return S_OK;
	}

	if (m_pCurrentScene->Get_SceneIndex() == pNextScene->Get_SceneIndex())
	{
		SafeRelease(pNextScene);
		return S_OK;
	}
	
	SafeRelease(m_pCurrentScene);
	m_pCurrentScene = pNextScene;

	return S_OK;
}

_uint CSceneManager::UpdateScene()
{
	if (nullptr == m_pCurrentScene)
		return ERROR;

	return m_pCurrentScene->UpdateScene();
}

_uint CSceneManager::LateUpdateScene()
{
	if (nullptr == m_pCurrentScene)
		return ERROR;

	return m_pCurrentScene->LateUpdateScene();
}

void CSceneManager::Free()
{
	SafeRelease(m_pCurrentScene);
}

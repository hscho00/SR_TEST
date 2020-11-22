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
		|| (pNextScene->Get_SceneIndex() == -1)) // m_iSceneIndex �� ������ �ֽÿ�
	{
		SafeRelease(pNextScene);	// �ۿ��� ������ ���� �Ѱ��ֹǷ� ������ release
									// m_pCurrentScene�� ��ȭ X
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

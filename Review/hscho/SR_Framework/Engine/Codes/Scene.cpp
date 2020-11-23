#include "..\Headers\Scene.h"

#include "TimeManager.h"
#include "GameObjectManager.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	, m_pTimeManager(CTimeManager::Get_Instance())
	, m_pGameObjectManager(CGameObjectManager::Get_Instance())
	, m_iSceneIndex(-1)
{
	// �ܺο��� ������ �����Ͱ� ������ ������ �����ʹ�,
	// �� �����͸� �ڱ⵵ �����Ѵ�(���������), �� AddRef() ������
	SafeAddRef(pDevice);
	SafeAddRef(m_pTimeManager);
	SafeAddRef(m_pGameObjectManager);
}

HRESULT CScene::ReadyScene()
{
	assert(m_pTimeManager);
	assert(m_pGameObjectManager);

	return S_OK;
}

_uint CScene::UpdateScene()
{
	return m_pGameObjectManager->UpdateGameObject(m_iSceneIndex, m_pTimeManager->Get_DeltaTime());
}

_uint CScene::LateUpdateScene()
{
	return m_pGameObjectManager->LateUpdateGameObject(m_iSceneIndex, m_pTimeManager->Get_DeltaTime());
}

void CScene::Free()
{
	// AddRef() ������ Release()�� ������
	SafeRelease(m_pGameObjectManager);
	SafeRelease(m_pTimeManager);
	SafeRelease(m_pDevice);
}

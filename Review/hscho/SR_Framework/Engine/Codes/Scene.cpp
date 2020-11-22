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
	// 외부에서 가져온 포인터가 누군가 소유한 포인터다,
	// 그 포인터를 자기도 소유한다(멤버변수로), 면 AddRef() 해주자
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
	// AddRef() 했으면 Release()도 해주자
	SafeRelease(m_pGameObjectManager);
	SafeRelease(m_pTimeManager);
	SafeRelease(m_pDevice);
}

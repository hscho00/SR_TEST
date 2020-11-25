#include "..\Headers\GameObjectManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGameObjectManager)

CGameObjectManager::CGameObjectManager()
	: m_pPrototypes(nullptr)
	, m_pLayers(nullptr)
	, m_iSceneCount(0)
	, m_bUseStatic(false)
	, m_iStaticScene(0)
{

}

HRESULT CGameObjectManager::ReserveContainer(_int iSceneCount, _bool isUseStaticScene, _int iStaticScene)
{
	if (0 > iSceneCount)
		return E_FAIL;

	m_iSceneCount = iSceneCount;
	m_bUseStatic = isUseStaticScene;
	m_iStaticScene = iStaticScene;

	m_pPrototypes = new PROTOTYPES[m_iSceneCount];
	if (nullptr == m_pPrototypes)
	{
		PRINT_LOG(L"Error", L"Failed To CGameObjectManager ReserveContainer");
		return E_FAIL;
	}

	m_pLayers = new LAYERS[m_iSceneCount];
	if (nullptr == m_pLayers)
	{
		PRINT_LOG(L"Error", L"Failed To CGameObjectManager ReserveContainer");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CGameObjectManager::AddGameObjectPrototype(_int iSceneIndex,
													const wstring& GameObjectTag,
													CGameObject* pPrototype)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range CGameObjectManager AddGameObjectPrototype");
		return E_FAIL;
	}

	assert(pPrototype);

	auto iter_find = m_pPrototypes[iSceneIndex].find(GameObjectTag);
	if (m_pPrototypes[iSceneIndex].end() == iter_find)
	{
		m_pPrototypes[iSceneIndex].insert(make_pair(GameObjectTag, pPrototype));
	}

	return S_OK;
}

HRESULT CGameObjectManager::AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range CGameObjectManager AddLayer");
		return E_FAIL;
	}

	auto iter_find = m_pLayers[iSceneIndex].find(LayerTag);
	if (m_pLayers[iSceneIndex].end() != iter_find)
	{
		PRINT_LOG(L"Warning", L"Exist Layer AddLayer");
		return E_FAIL;
	}

	m_pLayers[iSceneIndex].insert(make_pair(LayerTag, CLayer::Create(vecCapacity)));

	return S_OK;
}

HRESULT CGameObjectManager::AddGameObjectInLayer(_int iFromSceneIndex, 
												const wstring& GameObjectTag, 
												_int iToSceneIndex, 
												const wstring& LayerTag, 
												void* pArg/*= nullptr*/)
{
	if (0 > iFromSceneIndex ||
		m_iSceneCount <= iToSceneIndex ||
		0 > iToSceneIndex ||
		m_iSceneCount <= iToSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range CGameObjectManager AddGameObjectLayer");
		return E_FAIL;
	}
	
	auto iter_find = m_pPrototypes[iFromSceneIndex].find(GameObjectTag);
	if (m_pPrototypes[iFromSceneIndex].end() == iter_find)
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Not found %s Prototype", GameObjectTag.c_str());
		PRINT_LOG(L"Warning", szBuffer);
		return E_FAIL;
	}

	// 適経 持失!
	auto pClone = iter_find->second->Clone(pArg);
	if (nullptr == pClone)
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Failed To Clone %s Prototype", GameObjectTag.c_str());
		PRINT_LOG(L"Warning", szBuffer);
		return E_FAIL;
	}

	auto iter_find_Layer = m_pLayers[iToSceneIndex].find(LayerTag);
	if (m_pLayers[iToSceneIndex].end() == iter_find_Layer)
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Not found %s Layer", LayerTag.c_str());
		PRINT_LOG(L"Warning", szBuffer);
		return E_FAIL;
	}

	if (FAILED(m_pLayers[iToSceneIndex][LayerTag]->AddGameObjectInLayer(pClone)))
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Failed To AddGameObjectInLayer %s Clone", LayerTag.c_str());
		PRINT_LOG(L"Warning", szBuffer);
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CGameObjectManager::ClearForScene(_int iSceneIndex)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range CGameObjectManager ClearForScene");
		return E_FAIL;
	}

	for (auto& Pair : m_pLayers[iSceneIndex])
	{
		SafeRelease(Pair.second);
	}
	m_pLayers[iSceneIndex].clear();

	for (auto& Pair : m_pPrototypes[iSceneIndex])
	{
		SafeRelease(Pair.second);
	}
	m_pPrototypes[iSceneIndex].clear();

	return S_OK;
}

CGameObject* CGameObjectManager::GetGameObjectInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range CGameObjectManager GetGameObjectInLayerOrNull");
		return nullptr;
	}

	auto iter_find = m_pLayers[iSceneIndex].find(LayerTag);
	if (m_pLayers[iSceneIndex].end() == iter_find)
	{
		PRINT_LOG(L"Error", L"Not Found CGameObjectManager GetGameObjectInLayerOrNull");
		return nullptr;
	}

	return m_pLayers[iSceneIndex][LayerTag]->GetObjOrNull(idx);
}

_uint CGameObjectManager::UpdateGameObject(_int iSceneIndex, _float fDeltaTime)
{
	_uint ret = NO_EVENT;

	if (m_bUseStatic)
	{
		for (auto& Pair : m_pLayers[m_iStaticScene])
		{
			Pair.second->UpdateGameObject(fDeltaTime);
		}
	}

	for (auto& Pair : m_pLayers[iSceneIndex])
	{
		Pair.second->UpdateGameObject(fDeltaTime);
	}

	return ret;
}

_uint CGameObjectManager::LateUpdateGameObject(_int iSceneIndex, _float fDeltaTime)
{
	_uint ret = NO_EVENT;

	if (m_bUseStatic)
	{
		for (auto& Pair : m_pLayers[m_iStaticScene])
		{
			Pair.second->LateUpdateGameObject(fDeltaTime);
		}
	}

	for (auto& Pair : m_pLayers[iSceneIndex])
	{
		Pair.second->LateUpdateGameObject(fDeltaTime);
	}

	return ret;
}

//CGameObject* CGameObjectManager::CloneGameObjectPrototype(_int iSceneIndex,
//														const wstring& GameObjectTag,
//														void* pArg/*= nullptr*/)
//{
//	if (0 > iSceneIndex ||
//		m_iSceneCount <= iSceneIndex)
//	{
//		PRINT_LOG(L"Error", L"Out of range CGameObjectManager CloneGameObjectPrototype");
//		return nullptr;
//	}
//
//	auto iter_find = m_pPrototypes[iSceneIndex].find(GameObjectTag);
//	if (m_pPrototypes[iSceneIndex].end() == iter_find)
//	{
//		WCHAR szBuffer[128] = L"";
//		swprintf_s(szBuffer, L"Not found %s Prototype", GameObjectTag.c_str());
//		PRINT_LOG(L"Warning", szBuffer);
//		return nullptr;
//	}
//
//	return iter_find->second->Clone(pArg);
//}

void CGameObjectManager::Free()
{
	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			SafeRelease(Pair.second);
		}
		m_pLayers[i].clear();

		for (auto& Pair : m_pPrototypes[i])
		{
			SafeRelease(Pair.second);
		}
		m_pPrototypes[i].clear();
	}

	SafeDeleteArray(m_pLayers);
	SafeDeleteArray(m_pPrototypes);
}

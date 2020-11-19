#include "..\Headers\GameObjectManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(CGameObjectManager)

CGameObjectManager::CGameObjectManager()
	: m_pPrototypes(nullptr)
	, m_pLayers(nullptr)
	, m_iSceneCount(0)
{

}

HRESULT CGameObjectManager::ReservePrototypeContainer(_int iSceneCount)
{
	if (0 > iSceneCount)
		return E_FAIL;

	m_iSceneCount = iSceneCount;
	m_pPrototypes = new PROTOTYPES[m_iSceneCount];
	if (nullptr == m_pPrototypes)
	{
		PRINT_LOG(L"Error", L"Failed To GameObject ReservePrototypeContainer");
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
		PRINT_LOG(L"Error", L"Out of range GameObject AddGameObjectPrototype");
		return E_FAIL;
	}

	auto iter_find = m_pPrototypes[iSceneIndex].find(GameObjectTag);
	if (m_pPrototypes[iSceneIndex].end() == iter_find)
	{
		m_pPrototypes[iSceneIndex].insert(make_pair(GameObjectTag, pPrototype));
	}

	return S_OK;
}

CGameObject* CGameObjectManager::CloneGameObjectPrototype(_int iSceneIndex,
															const wstring& GameObjectTag,
															void* pArg)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range GameObject CloneGameObjectPrototype");
		return nullptr;
	}

	auto iter_find = m_pPrototypes[iSceneIndex].find(GameObjectTag);
	if (m_pPrototypes[iSceneIndex].end() == iter_find)
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Not found %s Prototype", GameObjectTag.c_str());

		PRINT_LOG(L"Warning", szBuffer);
		return nullptr;
	}

	return iter_find->second->Clone(pArg);
}

HRESULT CGameObjectManager::ClearForScene(_int iSceneIndex)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range GameObject ClearForScene");
		return E_FAIL;
	}

	for (auto& Pair : m_pPrototypes[iSceneIndex])
	{
		SafeRelease(Pair.second);
	}
	m_pPrototypes[iSceneIndex].clear();

	for (auto& Pair : m_pLayers[iSceneIndex])
	{
		SafeRelease(Pair.second);
	}
	m_pLayers[iSceneIndex].clear();

	return S_OK;
}

HRESULT CGameObjectManager::ReserveLayerContainer()
{
	m_pLayers = new LAYERS[m_iSceneCount];
	if (nullptr == m_pLayers)
	{
		PRINT_LOG(L"Error", L"Failed To GameObject ReserveLayerContainer");
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CGameObjectManager::AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range GameObject AddLayer");
		return E_FAIL;
	}

	auto iter_find = m_pLayers[iSceneIndex].find(LayerTag);
	if (m_pLayers[iSceneIndex].end() != iter_find)
	{
		PRINT_LOG(L"Error", L"Exist Layer AddLayer");
		return E_FAIL;
	}

	m_pLayers[iSceneIndex].insert(make_pair(LayerTag, CLayer::Create(vecCapacity)));

	return S_OK;
}

HRESULT CGameObjectManager::AddGameObjectInLayer(_int iSceneIndex, const wstring& LayerTag, CGameObject* pClone)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range GameObject AddGameObjectLayer");
		return E_FAIL;
	}

	auto iter_find = m_pLayers[iSceneIndex].find(LayerTag);
	if (m_pLayers[iSceneIndex].end() == iter_find)
	{
		PRINT_LOG(L"Error", L"Not Found Layer AddGameObjectLayer");
		return E_FAIL;
	}

	m_pLayers[iSceneIndex][LayerTag]->AddGameObjectInLayer(pClone);

	return S_OK;
}

CGameObject* CGameObjectManager::GetObjInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx)
{
	if (0 > iSceneIndex ||
		m_iSceneCount <= iSceneIndex)
	{
		PRINT_LOG(L"Error", L"Out of range GameObject GetCloneInLayer");
		return nullptr;
	}

	auto iter_find = m_pLayers[iSceneIndex].find(LayerTag);
	if (m_pLayers[iSceneIndex].end() == iter_find)
	{
		PRINT_LOG(L"Error", L"Not Found GameObject GetCloneInLayer");
		return nullptr;
	}

	return m_pLayers[iSceneIndex][LayerTag]->GetObjOrNull(idx);
}

//unordered_map<wstring, CLayer*>* CGameObjectManager::GetLayerOrNull(_int iSceneIndex) const
//{
//	if (0 > iSceneIndex ||
//		m_iSceneCount <= iSceneIndex)
//	{
//		PRINT_LOG(L"Error", L"Out of range GameObject GetLayerOrNull");
//		return nullptr;
//	}
//
//	return &m_pLayers[iSceneIndex];
//}

_uint CGameObjectManager::UpdateGameObject(_int iSceneIndex, float fDeltaTime)
{
	for (auto& Pair : m_pLayers[iSceneIndex])
	{
		Pair.second->UpdateGameObject(fDeltaTime);
	}

	return NO_EVENT;
}

_uint CGameObjectManager::LateUpdateGameObject(_int iSceneIndex, float fDeltaTime)
{
	for (auto& Pair : m_pLayers[iSceneIndex])
	{
		Pair.second->LateUpdateGameObject(fDeltaTime);
	}

	return NO_EVENT;
}

//////////////////////////////////////////////
HRESULT CGameObjectManager::RenderGameObject()
{
	// 일단 모든 씬을 다 돌고 나중에 렌더러 들어가면 없앨거임
	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->RenderGameObject();
		}
	}

	return NO_EVENT;
}
//////////////////////////////////////////////

void CGameObjectManager::Free()
{
	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pPrototypes[i])
		{
			SafeRelease(Pair.second);
		}
		m_pPrototypes[i].clear();

		for (auto& Pair : m_pLayers[i])
		{
			SafeRelease(Pair.second);
		}
		m_pLayers[i].clear();
	}

	SafeDeleteArray(m_pPrototypes);
	SafeDeleteArray(m_pLayers);
}

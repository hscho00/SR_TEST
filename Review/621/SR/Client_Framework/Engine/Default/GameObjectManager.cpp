#include "GameObjectManager.h"
#include "Layer.h"

USING(Engine)
IMPLEMENT_SINGLETON(GameObjectManager)

GameObjectManager::GameObjectManager()
{
}

HRESULT GameObjectManager::ReserveSizeContainer(_int iSceneCount)
{
	if (0 > iSceneCount)
		return E_FAIL;

	m_iSceneCount = iSceneCount;
	m_pPrototypes = new PROTOTYPES[m_iSceneCount];
	if (nullptr == m_pPrototypes)
	{
		LOG_MSG(L"Error", L"ReserveSizePrototypeContainer has failed");
		return E_FAIL;
	}

	m_pLayers = new LAYERS[m_iSceneCount];
	if (nullptr == m_pLayers)
	{
		LOG_MSG(L"Error", L"ReserveSizeLayeContainer has Failed");
		return E_FAIL;
	}


	return S_OK;
}

HRESULT GameObjectManager::AddGameObjectPrototype(
	_int iSceneIndex,
	const wstring& GameObjectTag,
	GameObject* pPrototype)
{
	if (0 > iSceneIndex || m_iSceneCount <= iSceneIndex)
	{
		LOG_MSG(L"Error", L"GameObject PrototypeContainer Out of range");
		return E_FAIL;
	}

	auto iter_find = m_pPrototypes[iSceneIndex].find(GameObjectTag);
	if (m_pPrototypes[iSceneIndex].end() == iter_find)
	{
		m_pPrototypes[iSceneIndex].insert(make_pair(GameObjectTag, pPrototype));
	}

	return S_OK;
}

HRESULT GameObjectManager::AddGameObjectinLayer(
	_int prototype_index, 
	const wstring& gameobject_tag, 
	_int clone_index, 
	const wstring& layer_tag, 
	void* pArg)
{
	if (0 > prototype_index || m_iSceneCount <= prototype_index)
	{
		LOG_MSG(L"Error", L"GameObject PrototypeContainer Out of range");
		return E_FAIL;
	}

	if (0 > clone_index || m_iSceneCount <= clone_index)
	{
		LOG_MSG(L"Error", L"GameObject CloneContainer Out of range");
		return E_FAIL;
	}

	auto iter_find = m_pPrototypes[prototype_index].find(gameobject_tag);
	if (m_pPrototypes[prototype_index].end() == iter_find)
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Not found %s Prototype", gameobject_tag.c_str());

		LOG_MSG(L"Error", szBuffer);
		return E_FAIL;
	}

	auto pClone = iter_find->second->Clone(pArg);
	if (nullptr == pClone)
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Failed To Clone %s Prototype", gameobject_tag.c_str());

		LOG_MSG(L"Error", szBuffer);
		return E_FAIL;
	}

	auto iter_find_Layer = m_pLayers[clone_index].find(layer_tag);
	if (m_pLayers[clone_index].end() == iter_find_Layer)
	{
		Layer* pLayer = Layer::Create();
		m_pLayers[clone_index].insert(make_pair(layer_tag, pLayer));
	}

	if (FAILED(m_pLayers[clone_index][layer_tag]->AddGameObjectInLayer(pClone)))
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Failed To AddGameObjectInLayer %s Clone", layer_tag.c_str());

		LOG_MSG(L"Warning", szBuffer);
		return E_FAIL;
	}

	return S_OK;
}

GameObject* GameObjectManager::CloneGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, void* pArg)
{
	if (0 > iSceneIndex || m_iSceneCount <= iSceneIndex)
	{
		LOG_MSG(L"Error", L"GameObject PrototypeContainer Out of range");
		return nullptr;
	}
	
	auto iter_find = m_pPrototypes[iSceneIndex].find(GameObjectTag);
	if (m_pPrototypes[iSceneIndex].end() == iter_find)
	{
		WCHAR szBuffer[128] = L"";
		swprintf_s(szBuffer, L"Not found %s Prototype", GameObjectTag.c_str());

		LOG_MSG(L"Error", szBuffer);
		return nullptr;
	}

	return iter_find->second->Clone(pArg);
}

HRESULT GameObjectManager::ClearForScene(_int iSceneIndex)
{
	if (0 > iSceneIndex || m_iSceneCount <= iSceneIndex)
	{
		LOG_MSG(L"Error", L"GameObject PrototypeContainer Out of range");
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

_uint GameObjectManager::UpdateGameObject(DOUBLE fDeltaTime)
{
	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->UpdateGameObject(fDeltaTime);
		}
	}

	return _uint();
}

_uint GameObjectManager::LateUpdateGameObject(DOUBLE fDeltaTime)
{
	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			Pair.second->LateUpdateGameObject(fDeltaTime);
		}
	}

	return _uint();
}

void GameObjectManager::Free()
{
	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			SafeRelease(Pair.second);
		}
		m_pLayers[i].clear();
	}

	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pPrototypes[i])
		{
			SafeRelease(Pair.second);
		}
		m_pPrototypes[i].clear();
	}

	SafeDeleteArray(m_pLayers);
	SafeDeleteArray(m_pPrototypes);
}

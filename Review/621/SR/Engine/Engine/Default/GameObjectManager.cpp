#include "GameObjectManager.h"

USING(Engine)
IMPLEMENT_SINGLETON(GameObjectManager)

GameObjectManager::GameObjectManager()
{
}

HRESULT GameObjectManager::ReserveSizePrototypeContainer(_int iSceneCount)
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

	return S_OK;
}

HRESULT GameObjectManager::AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, GameObject* pPrototype)
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


	for (auto& Pair : m_pPrototypes[iSceneIndex])
	{
		SafeRelease(Pair.second);
	}

	m_pPrototypes[iSceneIndex].clear();

	return S_OK;
}

_uint GameObjectManager::UpdateGameObject(float fDeltaTime)
{
	return _uint();
}

_uint GameObjectManager::LateUpdateGameObject(float fDeltaTime)
{
	return _uint();
}

void GameObjectManager::Free()
{
	for (_int i = 0; i < m_iSceneCount; ++i)
	{
		for (auto& Pair : m_pPrototypes[i])
		{
			SafeRelease(Pair.second);
		}
		m_pPrototypes[i].clear();
	}

	SafeDeleteArray(m_pPrototypes);
}

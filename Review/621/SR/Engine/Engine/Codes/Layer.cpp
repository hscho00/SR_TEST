#include "..\Headers\Layer.h"
#include "GameObject.h"

USING(Engine)

Layer::Layer()
{
}

HRESULT Layer::AddGameObjectInLayer(GameObject* pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	auto iter_find = find(m_GameObjects.begin(), m_GameObjects.end(), pGameObject);
	if (m_GameObjects.end() != iter_find)
	{
		LOG_MSG(L"Error", L"Already exist in current layer");
		return E_FAIL;
	}

	return S_OK;
}

_uint Layer::UpdateGameObject(float fDeltaTime)
{
	for (auto& pGameObject : m_GameObjects)
	{
		pGameObject->UpdateGameObject(fDeltaTime);
	}

	return _uint();
}

_uint Layer::LateUpdateGameObject(float fDeltaTime)
{
	for (auto& pGameObject : m_GameObjects)
	{
		pGameObject->LateUpdateGameObject(fDeltaTime);
	}

	return _uint();
}

void Layer::Free()
{
	for (auto& pGameObject : m_GameObjects)
	{
		SafeRelease(pGameObject);
	}

	m_GameObjects.clear();
}

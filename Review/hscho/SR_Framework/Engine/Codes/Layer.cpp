#include "..\Headers\Layer.h"
#include "GameObject.h"

USING(Engine)

CLayer::CLayer()
{

}

HRESULT CLayer::ReserveCloneContainer(_uint capacity)
{
	m_GameObjects.reserve(capacity);

	return S_OK;
}

HRESULT CLayer::AddGameObjectInLayer(CGameObject* pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	auto iter_find = find(m_GameObjects.begin(), m_GameObjects.end(), pGameObject);
	if (m_GameObjects.end() != iter_find)
	{
		PRINT_LOG(L"Warning", L"Already exist in current layer");
		return E_FAIL;
	}

	m_GameObjects.push_back(pGameObject);

	return S_OK;
}

_uint CLayer::UpdateGameObject(float fDeltaTime)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (!pGameObject->IsUsing())
			continue;

		_uint eventID = pGameObject->UpdateGameObject(fDeltaTime);
		if (eventID == OBJ_DEAD)
		{
			pGameObject->ReadyGameObject();
			pGameObject->Set_Dead(false);  // 다음에 사용될 때를 위해
			pGameObject->Set_Using(false);
		}
	}

	return NO_EVENT;
}

_uint CLayer::LateUpdateGameObject(float fDeltaTime)
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (!pGameObject->IsUsing())
			continue;

		pGameObject->LateUpdateGameObject(fDeltaTime);

		//if (pObj->IsDraw())
		//{
		//	unsigned int group = static_cast<unsigned int>(pObj->Get_RenderGroup());
		//	m_vecRenderSort[group].push_back(pObj);
		//}
	}

	return NO_EVENT;
}

CGameObject* CLayer::GetObjOrNull(_uint idx) const
{
	if (0 > idx ||
		m_GameObjects.size() <= idx)
	{
		PRINT_LOG(L"Error", L"Out of range CLayer GetObjOrNull");
		return nullptr;
	}

	return m_GameObjects[idx];
}

////////////////////////////////////////////////
HRESULT CLayer::RenderGameObject()
{
	for (auto& pGameObject : m_GameObjects)
	{
		if (!pGameObject->IsUsing())
			continue;

		if (!pGameObject->IsDraw())
			continue;

		pGameObject->RenderGameObject();
	}

	return S_OK;
}
////////////////////////////////////////////////

CLayer* CLayer::Create(_uint vecCapacity)
{
	CLayer* pInstance = new CLayer;
	pInstance->ReserveCloneContainer(vecCapacity);
	return pInstance;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_GameObjects)
	{
		SafeRelease(pGameObject);
	}

	m_GameObjects.clear();
}

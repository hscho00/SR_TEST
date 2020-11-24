#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain(_lpd3dd9 pDevice)
	: GameObject(pDevice)
{
}

Terrain::Terrain(const Terrain& other)
	: GameObject(other)
{
}

Terrain* Terrain::Create(_lpd3dd9 pDevice)
{
	assert(pDevice);

	Terrain* pInstance = new Terrain(pDevice);
	if (FAILED(pInstance->ReadyGameObjectPrototype()))
	{
		LOG_MSG(L"Error", L"Terrain Create has Failed");
		SafeRelease(pInstance);
	}

	return pInstance;
}

GameObject* Terrain::Clone(void* _pArg)
{
	Terrain* pClone = new Terrain(*this);

	if (FAILED(pClone->ReadyGameObject(_pArg)))
	{
		LOG_MSG(L"Error", L"Terrain clone creation failed.");
		SafeRelease(pClone);
	}

	return pClone;
}

void Terrain::Free()
{
	GameObject::Free();

	SafeRelease(m_pVIBufferCom);
}

HRESULT Terrain::ReadyGameObjectPrototype()
{
	if (FAILED(GameObject::ReadyGameObjectPrototype()))
		return E_FAIL;

	return S_OK;
}

HRESULT Terrain::ReadyGameObject(void* _pArg)
{
	if (FAILED(GameObject::ReadyGameObject(_pArg)))
	{
		return E_FAIL;
	}

	if (FAILED(AddComponent()))
	{
		return E_FAIL;
	}

	return S_OK;
}

_uint Terrain::UpdateGameObject(DOUBLE _fDeltaTime)
{
	GameObject::UpdateGameObject(_fDeltaTime);

	return _uint();
}

_uint Terrain::LateUpdateGameObject(DOUBLE _fDeltaTime)
{
	GameObject::LateUpdateGameObject(_fDeltaTime);

	auto pManagement = Management::Get_Instance();
	if (nullptr == pManagement)
	{
		return 0;
	}

	if (FAILED(pManagement->AddGameObjectInRenderer(RenderID::NOALPHA, this)))
		return 0;
	return _uint();
}

HRESULT Terrain::RenderGameObject()
{
	if (FAILED(GameObject::RenderGameObject()))
	{
		return E_FAIL;
	}

	if (FAILED(m_pVIBufferCom->Render_VIBuffer()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Terrain::AddComponent()
{
	/* TerrainVIBuffer */
	if (FAILED(GameObject::AddComponent(
		(_int)SceneID::Static,
		L"Component_VIBuffer_Terrain",
		L"Com_VITerrainBuffer",
		(Component**)&m_pVIBufferCom
	)))
	{
		return E_FAIL;
	}

	return S_OK;
}

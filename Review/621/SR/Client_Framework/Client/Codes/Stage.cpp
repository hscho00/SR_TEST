#include "stdafx.h"
#include "..\Headers\Stage.h"

Stage::Stage(LPDIRECT3DDEVICE9 pDevice)
    : Scene(pDevice)
{
}

HRESULT Stage::ReadyScene()
{
    Scene::ReadyScene();

	LOG_MSG(L"Stage", L"Stage");

	//if (FAILED(AddPlayerLayer(L"Layer_Player")))
	//	return E_FAIL;

	if (FAILED(AddTerrainLayer(L"Layer_Terrain")))
	{
		return E_FAIL;
	}

	return S_OK;
}

_uint Stage::UpdateScene()
{
    Scene::UpdateScene();

    return _uint();
}

_uint Stage::LateUpdateScene()
{
    Scene::LateUpdateScene();

    return _uint();
}

Stage* Stage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	Stage* pInstance = new Stage(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		LOG_MSG(L"Error", L"Preparation of StageScene has Failed");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void Stage::Free()
{
	Scene::Free();
}

HRESULT Stage::AddPlayerLayer(const wstring& LayerTag)
{
	auto pManagement = Management::Get_Instance();
	if (nullptr == pManagement)
		return E_FAIL;

	if (FAILED(pManagement->AddGameObjectInLayer(
		(_int)SceneID::Static, L"GameObject_Player",
		(_int)SceneID::Stage, LayerTag)))
		return E_FAIL;

	return S_OK;
}

HRESULT Stage::AddTerrainLayer(const wstring& LayerTag)
{
	auto pManagement = Management::Get_Instance();
	assert(pManagement);

	if (FAILED(pManagement->AddGameObjectInLayer(
		(_int)SceneID::Static, L"GameObject_Terrain",
		(_int)SceneID::Stage, LayerTag
	)))
	{
		return E_FAIL;
	}
	
	return S_OK;
}

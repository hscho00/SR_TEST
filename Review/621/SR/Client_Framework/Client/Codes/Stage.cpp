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

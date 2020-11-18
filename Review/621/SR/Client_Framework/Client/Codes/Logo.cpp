#include "stdafx.h"
#include "..\Headers\Logo.h"
#include "Stage.h"

Logo::Logo(LPDIRECT3DDEVICE9 pDevice)
	: Scene(pDevice)
{
}

HRESULT Logo::ReadyScene()
{
	Scene::ReadyScene();

	LOG_MSG(L"Logo", L"Logo");

	return S_OK;
}

_uint Logo::UpdateScene()
{
	Scene::UpdateScene();

	return _uint();
}

_uint Logo::LateUpdateScene()
{
	Scene::LateUpdateScene();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Management* pManagement = Management::Get_Instance();
		if (nullptr == pManagement)
			return 0;

		if (FAILED(pManagement->SetUpCurrentScene((_int)SceneID::Stage,
			Stage::Create(m_pDevice))))
		{
			LOG_MSG(L"Error", L"SetUpCurrentScene has Failed");
			return 0;
		}

		return CHANGE_SCNENE;
	}
	return _uint();
}

Logo* Logo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	Logo* pInstance = new Logo(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		LOG_MSG(L"Error", L"Preparation of LogoScene has Failed");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void Logo::Free()
{
	Scene::Free();
}

#include "..\Headers\Renderer.h"
#include "GameObject.h"

USING(Engine)
IMPLEMENT_SINGLETON(Renderer)

Renderer::Renderer()
{
}

Renderer* Renderer::Create(_lpd3dd9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	Renderer* Instance = Renderer::Get_Instance();

	if (!(Instance->get_Setting()))
	{
		Instance->Ready_Renderer(pDevice);
	}

	return Instance;
}

void Renderer::Free()
{
	for (_int i = 0; i < (_int)RenderID::MAX; ++i)
	{
		for (auto& pObject : m_GameObjects[i])
		{
			SafeRelease(pObject);
		}

		m_GameObjects[i].clear();
	}

	SafeRelease(m_pDevice);
}

HRESULT Renderer::AddGameObjectInRenderer(RenderID Id, GameObject* GameObject)
{
	if (0 > (_int)Id ||
		RenderID::MAX <= Id)
	{
		LOG_MSG(L"Error", L"Out of range Render list");
		return E_FAIL;
	}

	if (nullptr == GameObject)
		return E_FAIL;

	m_GameObjects[(_int)Id].push_back(GameObject);
	SafeAddRef(GameObject);

	return S_OK;
}

HRESULT Renderer::Render(HWND hWnd)
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();
	
	if (FAILED(RenderPriority()))
		return E_FAIL;

	if (FAILED(RenderNoAlpha()))
		return E_FAIL;

	if (FAILED(RenderAlpha()))
		return E_FAIL;

	if (FAILED(RenderUi()))
		return E_FAIL;

	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);

	return S_OK;
}

HRESULT Renderer::Ready_Renderer(_lpd3dd9 pDevice)
{
	bSetting = TRUE;
	m_pDevice = pDevice;
	SafeAddRef(m_pDevice);
	return S_OK;
}

HRESULT Renderer::RenderPriority()
{
	for (auto& pObject : m_GameObjects[(_int)RenderID::PRIORITY])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_int)RenderID::PRIORITY].clear();

	return S_OK;
}

HRESULT Renderer::RenderNoAlpha()
{
	for (auto& pObject : m_GameObjects[(_int)RenderID::NOALPHA])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_int)RenderID::NOALPHA].clear();

	return S_OK;
}

HRESULT Renderer::RenderAlpha()
{
	for (auto& pObject : m_GameObjects[(_int)RenderID::ALPHA])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_int)RenderID::ALPHA].clear();
	return S_OK;
}

HRESULT Renderer::RenderUi()
{
	for (auto& pObject : m_GameObjects[(_int)RenderID::UI])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_int)RenderID::UI].clear();
	return S_OK;
}

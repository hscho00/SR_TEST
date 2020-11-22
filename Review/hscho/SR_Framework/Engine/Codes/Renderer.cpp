#include "..\Headers\Renderer.h"
#include "GameObject.h"

USING(Engine)
IMPLEMENT_SINGLETON(CRenderer)

CRenderer::CRenderer()
	: m_pDevice(nullptr)
{

}

HRESULT CRenderer::ReadyRenderer(LPDIRECT3DDEVICE9 pDevice/*, _uint vecCapacity*/)
{
	m_pDevice = pDevice;
	SafeAddRef(m_pDevice);

	// 더 좋은 방법 없을까?
	for (_uint i = 0; i < (_uint)ERenderID::MaxCount; ++i)
		m_GameObjects[i].reserve(100);	// 대충 크게 잡아놓음. 나중에 테스트 하면서 수정.

	return S_OK;
}

/* 매 프레임마다 렌더 vector에 오브젝트를 추가한다. */
HRESULT CRenderer::AddGameObjectInRenderer(ERenderID eID, CGameObject* pGameObject)
{
	if (nullptr == m_pDevice)
	{
		PRINT_LOG(L"Error", L"Device is NULL AddGameObjectInRenderer");
		return E_FAIL;
	}

	if (ERenderID::MaxCount <= eID)
	{
		PRINT_LOG(L"Error", L"Out of range AddGameObjectInRenderer");
		return E_FAIL;
	}

	if (nullptr == pGameObject)
	{
		PRINT_LOG(L"Warning", L"GameObject is NULL AddGameObjectInRenderer");
		return E_FAIL;
	}

	m_GameObjects[(_uint)eID].push_back(pGameObject);
	SafeAddRef(pGameObject);

	return E_NOTIMPL;
}

HRESULT CRenderer::Render(HWND hWnd)
{
	m_pDevice->Clear(0, nullptr, D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();

	if (FAILED(RenderPriority()))
		return E_FAIL;

	if (FAILED(RenderNoAlpha()))
		return E_FAIL;

	if (FAILED(RenderAlpha()))
		return E_FAIL;

	if (FAILED(RenderUI()))
		return E_FAIL;

	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);

	return S_OK;
}

HRESULT CRenderer::RenderPriority()
{
	for (auto& pObject : m_GameObjects[(_uint)ERenderID::Priority])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_uint)ERenderID::Priority].clear();

	return S_OK;
}

HRESULT CRenderer::RenderNoAlpha()
{
	for (auto& pObject : m_GameObjects[(_uint)ERenderID::NoAlpha])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_uint)ERenderID::NoAlpha].clear();

	return S_OK;
}

HRESULT CRenderer::RenderAlpha()
{
	for (auto& pObject : m_GameObjects[(_uint)ERenderID::Alpha])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_uint)ERenderID::Alpha].clear();

	return S_OK;
}

HRESULT CRenderer::RenderUI()
{
	for (auto& pObject : m_GameObjects[(_uint)ERenderID::UI])
	{
		if (FAILED(pObject->RenderGameObject()))
			return E_FAIL;

		SafeRelease(pObject);
	}

	m_GameObjects[(_uint)ERenderID::UI].clear();

	return S_OK;
}

void CRenderer::Free()
{
	for (_int i = 0; i < (_uint)ERenderID::MaxCount; ++i)
	{
		for (auto& pObject : m_GameObjects[i])
		{
			SafeRelease(pObject);
		}

		m_GameObjects[i].clear();
		m_GameObjects[i].shrink_to_fit();
	}

	SafeRelease(m_pDevice);
}

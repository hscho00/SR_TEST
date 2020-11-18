#include "..\Headers\Management.h"

USING(Engine)
IMPLEMENT_SINGLETON(Management)

Management::Management()
	: m_pGraphic_Dev(GraphicDevice::Get_Instance())
	, m_pSceneManager(SceneManager::Get_Instance())
{
	SafeAddRef(m_pGraphic_Dev);
	SafeAddRef(m_pSceneManager);
}

HRESULT Management::ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, DisplayMode eDisplaymode)
{
	if (FAILED(m_pGraphic_Dev->ReadyGraphicDevice(hWnd, iWinCX, iWinCY, eDisplaymode)))
		return E_FAIL;

	return S_OK;
}

_uint Management::UpdateEngine()
{
	if (nullptr == m_pSceneManager)
		return 0;

	m_iUpdateEvent = m_pSceneManager->UpdateScene();
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	m_iUpdateEvent = m_pSceneManager->LateUpdateScene();
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	return _uint();
}

_uint Management::RenderEngine()
{
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	m_pGraphic_Dev->RenderBegin();

	m_pGraphic_Dev->RenderEnd();

	return _uint();
}

LPDIRECT3DDEVICE9 Management::GetDevice()
{
	if (nullptr == m_pGraphic_Dev)
		return nullptr;

	return m_pGraphic_Dev->Get_Device_();
}

HRESULT Management::SetUpCurrentScene(_int iSceneID, Scene* pCurrentScene)
{
	if (nullptr == m_pSceneManager)
		return E_FAIL;

	return m_pSceneManager->SetUpCurrentScene(iSceneID, pCurrentScene);
}

void Management::Free()
{
	SafeRelease(m_pSceneManager);
	SafeRelease(m_pGraphic_Dev);
}

void Management::ReleaseEngine()
{
	if (Management::Destroy_Instance())
		LOG_MSG(L"Warning", L"Management release failed.");

	if (SceneManager::Destroy_Instance())
		LOG_MSG(L"Warning", L"SceneManager release failed.");

	if (GraphicDevice::Destroy_Instance())
		LOG_MSG(L"Warning", L"GraphicDevice release failed.");
}

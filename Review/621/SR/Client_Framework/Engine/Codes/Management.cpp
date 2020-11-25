#include "..\Headers\Management.h"

USING(Engine)
IMPLEMENT_SINGLETON(Management)

Management::Management()
	: m_pGraphic_Dev(GraphicDevice::Get_Instance())
	, m_pSceneManager(SceneManager::Get_Instance())
	, m_pTimeManager(TimeManager::Get_Instance())
	, m_pGameObjectManager(GameObjectManager::Get_Instance())
	, m_pComponentManager(ComponentManager::Get_Instance())
	, m_pRenderer(Renderer::Get_Instance())
	, m_pKeyManager(KeyManager::Get_Instance())
{
	SafeAddRef(m_pGraphic_Dev);
	SafeAddRef(m_pRenderer);
	SafeAddRef(m_pTimeManager);
	SafeAddRef(m_pSceneManager);
	SafeAddRef(m_pGameObjectManager);
	SafeAddRef(m_pComponentManager);
}

HRESULT Management::ReadyEngine(
	HWND hWnd,
	_uint iWinCX,
	_uint iWinCY,
	DisplayMode eDisplaymode,
	_uint iSceneCount)
{
	if (FAILED(m_pGraphic_Dev->ReadyGraphicDevice(hWnd, iWinCX, iWinCY, eDisplaymode)))
		return E_FAIL;

	if (FAILED(m_pGameObjectManager->ReserveSizeContainer(iSceneCount)))
		return E_FAIL;

	if (FAILED(m_pComponentManager->ReserveSizePrototypeContainer(iSceneCount)))
		return E_FAIL;

	m_pRenderer = Renderer::Create(m_pGraphic_Dev->Get_Device_());
	if (m_pRenderer == nullptr)
	{
		LOG_MSG(L"Error", L"Failed To Create Renderer");
		return E_FAIL;
	}

	return S_OK;
}

_uint Management::UpdateEngine()
{
	if (nullptr == m_pSceneManager)
		return 0;

	/* for.DeltaTime*/
	m_pTimeManager->UpdateTimeManager();
	fDeltaTime = m_pTimeManager->Get_DeltaTime();

	/* for.Update */
	m_iUpdateEvent = m_pSceneManager->UpdateScene();
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	m_iUpdateEvent = m_pGameObjectManager->UpdateGameObject(fDeltaTime);
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	return _uint();
}

_uint Management::LateUpdateEngine()
{
	/* for.DeltaTime*/
	fDeltaTime = m_pTimeManager->Get_DeltaTime();

	m_iUpdateEvent = m_pSceneManager->LateUpdateScene();
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	m_iUpdateEvent = m_pGameObjectManager->LateUpdateGameObject(fDeltaTime);
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	return _uint();
}

_uint Management::RenderEngine(HWND hWnd)
{
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Render(hWnd);
}

HRESULT Management::ClearForScene(_int iSceneIndex)
{
	if (FAILED(m_pGameObjectManager->ClearForScene(iSceneIndex)))
		return E_FAIL;

	if (FAILED(m_pComponentManager->ClearForScene(iSceneIndex)))
		return E_FAIL;

	return S_OK;;
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

HRESULT Management::AddGameObjectPrototype(
	_int iSceneIndex, 
	const wstring& GameObjectTag, 
GameObject* pPrototype)
{
	if (nullptr == m_pGameObjectManager)
		return E_FAIL;

	return m_pGameObjectManager->AddGameObjectPrototype(iSceneIndex, GameObjectTag, pPrototype);
}

HRESULT Management::AddGameObjectInLayer(
	_int iFromSceneIndex, 
	const wstring& GameObjectTag, 
	_int iToSceneIndex, 
	const wstring& LayerTag, 
	void* pArg)
{
	assert(m_pGameObjectManager);

	return m_pGameObjectManager->AddGameObjectinLayer(iFromSceneIndex, GameObjectTag, iToSceneIndex, LayerTag, pArg);
}

HRESULT Management::AddComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, Component* pPrototype)
{
	if (nullptr == m_pComponentManager)
		return E_FAIL;

	return m_pComponentManager->AddComponentPrototype(iSceneIndex, ComponentTag, pPrototype);
}

Component* Management::CloneComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, void* pArg)
{
	if (nullptr == m_pComponentManager)
		return nullptr;

	return m_pComponentManager->CloneComponentPrototype(iSceneIndex, ComponentTag, pArg);
}

HRESULT Management::AddGameObjectInRenderer(RenderID eID, GameObject* pGameObject)
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->AddGameObjectInRenderer(eID, pGameObject);
}

void Management::Free()
{
	SafeRelease(m_pRenderer);
	SafeRelease(m_pGameObjectManager);
	SafeRelease(m_pComponentManager);
	SafeRelease(m_pSceneManager);
	SafeRelease(m_pTimeManager);
	SafeRelease(m_pGraphic_Dev);
}

void Management::ReleaseEngine()
{
	if (Management::Destroy_Instance())
		LOG_MSG(L"Warning", L"Management release failed.");

	if(GameObjectManager::Destroy_Instance())
		LOG_MSG(L"Warning", L"GameObjectManager release failed.")

	if (ComponentManager::Destroy_Instance())
		LOG_MSG(L"Warning", L"ComponentManager release failed.");

	if (Renderer::Destroy_Instance())
		LOG_MSG(L"Warning", L"Renderer release failed.");

	if (SceneManager::Destroy_Instance())
		LOG_MSG(L"Warning", L"SceneManager release failed.");

	if (TimeManager::Destroy_Instance())
		LOG_MSG(L"Warning", L"TimeManager release failed.");

	if (GraphicDevice::Destroy_Instance())
		LOG_MSG(L"Warning", L"GraphicDevice release failed.");
}

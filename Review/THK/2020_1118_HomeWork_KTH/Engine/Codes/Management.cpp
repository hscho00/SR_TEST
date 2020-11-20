#include "..\Headers\Management.h"

USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
	: m_pGraphic_Dev(CGraphic_Device::Get_Instance())
	, m_pSceneManager(CSceneManager::Get_Instance())
	, m_pComponentManager(CComponentManager::Get_Instance())
	, m_pGameObjectManager(CGameObjectManager ::Get_Instance())
	, m_pTimeManager(CTime_Manager::Get_Instance())
	
{
	SafeAddRef(m_pGraphic_Dev);
	SafeAddRef(m_pSceneManager);
	SafeAddRef(m_pGameObjectManager);
	SafeAddRef(m_pComponentManager);
	SafeAddRef(m_pTimeManager);
}

HRESULT CManagement::ReadyEngine(
	HWND hWnd, 
	_uint iWinCX,
	_uint iWinCY, 
	EDisplayMode eDisplaymode,
	_uint iSceneCount)
{
	if (FAILED(m_pGraphic_Dev->Ready_Graphic_Device(hWnd, iWinCX, iWinCY, eDisplaymode)))
		return E_FAIL;
	if (FAILED(m_pGameObjectManager->ReserveSizePrototypeContainer(iSceneCount)))
		return E_FAIL;
	if (FAILED(m_pComponentManager->ReserveSizePrototypeContainer(iSceneCount)))
		return E_FAIL;
	
	m_pRenderer = CRenderer::Create(m_pGraphic_Dev->Get_Device());
	if (nullptr == m_pRenderer)
	{
		PRINT_LOG(L"Error", L"Failed To Create Renderer");
		return E_FAIL;
	}


	return S_OK;
}

_uint CManagement::UpdateEngine()
{
	if (nullptr == m_pSceneManager)
		return 0;
	//for DeltaTime
	float fDeltaTime = m_pTimeManager->Update_Time_Manager();

	//Update
	m_iUpdateEvent = m_pSceneManager->UpdateScene();
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	m_iUpdateEvent = m_pGameObjectManager->UpdateGameObject(fDeltaTime);


	//LateUpdate
	m_iUpdateEvent = m_pSceneManager->LateUpdateScene();
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;
	m_iUpdateEvent = m_pGameObjectManager->LateUpdateGameObject(fDeltaTime);

	return _uint();
}

_uint CManagement::RenderEngine(HWND hWnd)
{
	if (CHANGE_SCNENE == m_iUpdateEvent)
		return m_iUpdateEvent;

	if (nullptr == m_pRenderer)
		return E_FAIL;
	return m_pRenderer->Render(hWnd);
}

HRESULT CManagement::ClearForScene(_int iSceneIndex)
{
	if (FAILED(m_pGameObjectManager->ClearForScene(iSceneIndex)))
		return E_FAIL;

	if (FAILED(m_pComponentManager->ClearForScene(iSceneIndex)))
		return E_FAIL;

	return E_NOTIMPL;
}

LPDIRECT3DDEVICE9 CManagement::GetDevice()
{
	if (nullptr == m_pGraphic_Dev)
		return nullptr;

	return m_pGraphic_Dev->Get_Device();
}

HRESULT CManagement::SetUpCurrentScene(_int iSceneID, CScene * pCurrentScene)
{
	if (nullptr == m_pSceneManager)
		return E_FAIL;

	return m_pSceneManager->SetUpCurrentScene(iSceneID, pCurrentScene);
}

HRESULT CManagement::AddGameObjectPrototype(
	_int iSceneIndex, 
	const wstring & GameObjectTag, 
	CGameObject * pPrototype)
{
	if (nullptr == m_pGameObjectManager)
		return E_FAIL;

	return m_pGameObjectManager->AddGameObjectPrototype(iSceneIndex, GameObjectTag, pPrototype);
}

HRESULT CManagement::AddGameObjectInLayer(
	_int iFromSceneIndex, 
	const wstring & GameObjectTag, 
	_int iToSceneIndex, 
	const wstring & LayerTag,
	void * pArg)
{
	if (nullptr == m_pGameObjectManager)
		return E_FAIL;

	return m_pGameObjectManager->AddGameObjectInLayer(iFromSceneIndex, GameObjectTag, iToSceneIndex, LayerTag, pArg);
}

HRESULT CManagement::AddComponentPrototype(_int iSceneIndex, const wstring & ComponentTag, CComponent * pPrototype)
{
	if (nullptr == m_pComponentManager)
		return E_FAIL;

	return m_pComponentManager->AddComponentprototype(iSceneIndex, ComponentTag, pPrototype);
}

CComponent * CManagement::CloneComponentPrototype(
	_int iSceneIndex, 
	const wstring & ComponentTag, 
	void * pArg)
{
	if (nullptr == m_pComponentManager)
		return nullptr;


	
	return m_pComponentManager->CloneComponentPrototype(iSceneIndex, ComponentTag, pArg);
}

HRESULT CManagement::AddGameObjectInRenderer(ERenderID eID, CGameObject * pGameObject)
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	
	return m_pRenderer->AddGameObjectInRenderer(eID, pGameObject);
}

void CManagement::Free()
{
	SafeRelease(m_pRenderer);
	SafeRelease(m_pGameObjectManager);
	SafeRelease(m_pComponentManager);
	SafeRelease(m_pSceneManager);
	SafeRelease(m_pTimeManager);
	SafeRelease(m_pGraphic_Dev);
}

void CManagement::ReleaseEngine()
{
	if(CManagement::Destroy_Instance())
		PRINT_LOG(L"Warning", L"Failed To Release CManagement");

	if (CGameObjectManager::Destroy_Instance())
		PRINT_LOG(L"Warning", L"Failed To Release CGameObjectManager");

	if (CComponentManager::Destroy_Instance())
		PRINT_LOG(L"Warning", L"Failed To Release CComponentManager");
		
	if (CSceneManager::Destroy_Instance())
		PRINT_LOG(L"Warning", L"Failed To Release CSceneManager");

	if (CGraphic_Device::Destroy_Instance())
		PRINT_LOG(L"Warning", L"Failed To Release CGraphic_Device");
}

#include "..\Headers\Management.h"


USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
    : m_pGraphic_Dev(CGraphic_Device::Get_Instance())
    , m_pTimeManager(CTimeManager::Get_Instance())
    , m_pGameObjectManager(CGameObjectManager::Get_Instance())
    , m_pSceneManager(CSceneManager::Get_Instance())
    , m_pComponentManager(CComponentManager::Get_Instance())
    , m_pRenderer(CRenderer::Get_Instance())
    , m_iUpdateEvent(0)
{
    SafeAddRef(m_pGraphic_Dev);
    SafeAddRef(m_pTimeManager);
    SafeAddRef(m_pGameObjectManager);
    SafeAddRef(m_pSceneManager);
    SafeAddRef(m_pComponentManager);
    SafeAddRef(m_pRenderer);
}

HRESULT CManagement::ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplaymode,
                                _int iSceneCount, _bool isUseStaticScen5e/*= false*/, _int iStaticScene/*= 0*/)
{
    assert(m_pGraphic_Dev);
    assert(m_pTimeManager);
    assert(m_pGameObjectManager);
    assert(m_pSceneManager);
    assert(m_pComponentManager);
    assert(m_pRenderer);

    if (FAILED(m_pGraphic_Dev->Ready_Graphic_Device(hWnd, iWinCX, iWinCY, eDisplaymode)))
        return E_FAIL;

    if (FAILED(m_pTimeManager->ReadyTimeManager()))
        return E_FAIL;

    //if (FAILED(m_pGameObjectManager->ReserveContainer(iSceneCount, isUseStaticScene, iStaticScene)))
    //    return E_FAIL;

    if (FAILED(m_pComponentManager->ReservePrototypeContainer(iSceneCount)))
        return E_FAIL;

    if (FAILED(m_pRenderer->ReadyRenderer(m_pGraphic_Dev->Get_Device())))
        return E_FAIL;

    return S_OK;
}

_uint CManagement::UpdateEngine()
{
    m_pTimeManager->UpdateTimeManager();

    m_iUpdateEvent = m_pSceneManager->UpdateScene();
    if (CHANGE_SCENE == m_iUpdateEvent)
        return m_iUpdateEvent;
    else if (ERROR == m_iUpdateEvent)
        return m_iUpdateEvent;

    m_iUpdateEvent = m_pSceneManager->LateUpdateScene();
    if (CHANGE_SCENE == m_iUpdateEvent)
        return m_iUpdateEvent;
    else if (ERROR == m_iUpdateEvent)
        return m_iUpdateEvent;

    return m_iUpdateEvent;
}

_uint CManagement::RenderEngine(HWND hWnd/*= nullptr*/)
{
    if (CHANGE_SCENE == m_iUpdateEvent)
        return m_iUpdateEvent;

    return m_pRenderer->Render(hWnd);
}

HRESULT CManagement::ClearForScene(_int iSceneIndex)
{
    if (FAILED(m_pComponentManager->ClearForScene(iSceneIndex)))
        return E_FAIL;

    if (FAILED(m_pGameObjectManager->ClearForScene(iSceneIndex)))
        return E_FAIL;

    return S_OK;
}

LPDIRECT3DDEVICE9 CManagement::GetDevice()
{
    return m_pGraphic_Dev->Get_Device();
}

HRESULT CManagement::SetUpCurrentScene(CScene* pCurrentScene)
{
    return m_pSceneManager->SetUpCurrentScene(pCurrentScene);
}

HRESULT CManagement::AddGameObjectPrototype(_int iSceneIndex, const wstring& GameObjectTag, CGameObject* pPrototype)
{
    return m_pGameObjectManager->AddGameObjectPrototype(iSceneIndex, GameObjectTag, pPrototype);
}

HRESULT CManagement::AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity)
{
    return m_pGameObjectManager->AddLayer(iSceneIndex, LayerTag, vecCapacity);
}

HRESULT CManagement::AddGameObjectInLayer(_int iFromSceneIndex, const wstring& GameObjectTag, _int iToSceneIndex, const wstring& LayerTag, void* pArg/*= nullptr*/)
{
    return m_pGameObjectManager->AddGameObjectInLayer(iFromSceneIndex, GameObjectTag, iToSceneIndex, LayerTag, pArg);
}

CGameObject* CManagement::GetGameObjectInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx)
{
    return m_pGameObjectManager->GetGameObjectInLayerOrNull(iSceneIndex, LayerTag, idx);
}

HRESULT CManagement::AddComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, CComponent* pPrototype)
{
    return m_pComponentManager->AddComponentPrototype(iSceneIndex, ComponentTag, pPrototype);
}

CComponent* CManagement::CloneComponentPrototype(_int iSceneIndex, const wstring& ComponentTag, void* pArg)
{
    return m_pComponentManager->CloneComponentPrototype(iSceneIndex, ComponentTag, pArg);
}

HRESULT CManagement::AddGameObjectInRenderer(ERenderID eID, CGameObject* pGameObject)
{
    return m_pRenderer->AddGameObjectInRenderer(eID, pGameObject);
}

void CManagement::Free()
{
    SafeRelease(m_pRenderer);
    SafeRelease(m_pComponentManager);
    SafeRelease(m_pSceneManager);           // scene에서 gameobjectmgr를 참조하므로 먼저 지워주자
    SafeRelease(m_pGameObjectManager);
    SafeRelease(m_pTimeManager);
    SafeRelease(m_pGraphic_Dev);    // Graphice Device를 마지막에
}

void CManagement::ReleaseEngine()
{
    // 자기를 먼저 지워야 Free()에서 RefCnt를 감소시킴
    if (CManagement::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CManagement");

    // RefCnt가 0인 상태에서 Release를 해야 제대로 지워짐
    if (CRenderer::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CRenderer");

    if (CComponentManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CComponentManager");

    if (CSceneManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CSceneManager");

    if (CGameObjectManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CGameObjectManager");

    if (CTimeManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CTimeManager");

    if (CGraphic_Device::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CGraphic_Device");
}
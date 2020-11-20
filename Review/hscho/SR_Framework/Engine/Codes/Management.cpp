#include "..\Headers\Management.h"


USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
    : m_pGraphic_Dev(CGraphic_Device::Get_Instance())
    , m_pSceneManager(CSceneManager::Get_Instance())
    , m_pGameObjectManager(CGameObjectManager::Get_Instance())
    , m_pComponentManager(CComponentManager::Get_Instance())
    , m_pTimeManager(CTimeManager::Get_Instance())
    , m_iUpdateEvent(0)
{
    SafeAddRef(m_pGraphic_Dev);
    SafeAddRef(m_pSceneManager);
    SafeAddRef(m_pGameObjectManager);
    SafeAddRef(m_pComponentManager);
    SafeAddRef(m_pTimeManager);
}

HRESULT CManagement::ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplaymode)
{
    if (FAILED(m_pGraphic_Dev->Ready_Graphic_Device(hWnd, iWinCX, iWinCY, eDisplaymode)))
        return E_FAIL;

    if (FAILED(m_pTimeManager->Ready_TimeMgr()))
        return E_FAIL;

    return S_OK;
}

_uint CManagement::UpdateEngine()
{
    if (nullptr == m_pSceneManager)
    {
        m_iUpdateEvent = ERROR;
        return m_iUpdateEvent;
    }

    m_pTimeManager->Compute_TimeMgr();

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

_uint CManagement::RenderEngine()
{
    if (CHANGE_SCENE == m_iUpdateEvent)
        return m_iUpdateEvent;

    m_pGraphic_Dev->Render_Begin();

    // 다른씬에 있는것도 체크하기 때문에 아직 비효율적
    m_pGameObjectManager->RenderGameObject();

    m_pGraphic_Dev->Render_End();

    return m_iUpdateEvent;
}

LPDIRECT3DDEVICE9 CManagement::GetDevice()
{
    if (nullptr == m_pGraphic_Dev)
        return nullptr;

    return m_pGraphic_Dev->Get_Device();
}

HRESULT CManagement::SetUpCurrentScene(_int iSceneID, CScene* pCurrentScene)
{
    if (nullptr == m_pSceneManager)
        return E_FAIL;

    return m_pSceneManager->SetUpCurrentScene(iSceneID, pCurrentScene);
}

HRESULT CManagement::ReadyGameObjectManager(_int iSceneCount)
{
    m_pGameObjectManager->ReservePrototypeContainer(iSceneCount);
    m_pGameObjectManager->ReserveLayerContainer();

    return S_OK;
}

HRESULT CManagement::AddObjPrototype(_int iSceneIndex, const wstring& GameObjectTag, CGameObject* pPrototype)
{
    return m_pGameObjectManager->AddGameObjectPrototype(iSceneIndex, GameObjectTag, pPrototype);
}

CGameObject* CManagement::CloneObjPrototype(_int iSceneIndex, const wstring& GameObjectTag, void* pArg)
{
    return m_pGameObjectManager->CloneGameObjectPrototype(iSceneIndex, GameObjectTag, pArg);
}

HRESULT CManagement::ClearForScene(_int iSceneIndex)
{
    return m_pGameObjectManager->ClearForScene(iSceneIndex);
}

HRESULT CManagement::AddLayer(_int iSceneIndex, const wstring& LayerTag, _uint vecCapacity)
{
    return m_pGameObjectManager->AddLayer(iSceneIndex, LayerTag, vecCapacity);
}

HRESULT CManagement::AddObjInLayer(_int iSceneIndex, const wstring& LayerTag, CGameObject* pClone)
{
    return m_pGameObjectManager->AddGameObjectInLayer(iSceneIndex, LayerTag, pClone);
}

CGameObject* CManagement::GetObjInLayerOrNull(_int iSceneIndex, const wstring& LayerTag, _uint idx)
{
    return m_pGameObjectManager->GetObjInLayerOrNull(iSceneIndex, LayerTag, idx);
}

HRESULT CManagement::UpdateGameObject(_int iSceneIndex)
{
    return m_pGameObjectManager->UpdateGameObject(iSceneIndex, m_pTimeManager->Get_DeltaTime());
}

HRESULT CManagement::LateUpdateGameObject(_int iSceneIndex)
{
    return m_pGameObjectManager->LateUpdateGameObject(iSceneIndex, m_pTimeManager->Get_DeltaTime());
}

void CManagement::Free()
{
    SafeRelease(m_pTimeManager);
    SafeRelease(m_pComponentManager);
    SafeRelease(m_pGameObjectManager);
    SafeRelease(m_pSceneManager);
    SafeRelease(m_pGraphic_Dev);    // Graphice Device를 마지막에
}

void CManagement::ReleaseEngine()
{
    // 자기를 먼저 지워야 Free()에서 RefCnt를 감소시킴
    if (CManagement::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CManagement");

    // RefCnt가 0인 상태에서 Release를 해야 제대로 지워짐
    if (CTimeManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CTimeManager");

    if (CComponentManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CComponentManager");

    if (CSceneManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CSceneManager");

    if (CGameObjectManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CGameObjectManager");

    if (CGraphic_Device::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CGraphic_Device");
}
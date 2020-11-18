#include "..\Headers\Management.h"


USING(Engine)
IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
    : m_pGraphic_Dev(CGraphic_Device::Get_Instance())
    , m_pSceneManager(CSceneManager::Get_Instance())
    , m_iUpdateEvent(0)
{
    SafeAddRef(m_pGraphic_Dev);
    SafeAddRef(m_pSceneManager);
}

HRESULT CManagement::ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, EDisplayMode eDisplaymode)
{
    if (FAILED(m_pGraphic_Dev->Ready_Graphic_Device(hWnd, iWinCX, iWinCY, eDisplaymode)))
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

    /////////////////////////////////////////////////
    for (auto pVertices : m_vecVertices)
    {
        m_pGraphic_Dev->Get_Device()->SetTransform(D3DTS_WORLD, &pVertices->Get_MatWorld());

        m_pGraphic_Dev->Get_Device()->SetStreamSource(0, pVertices->Get_VertexBuffer(), 0, sizeof(Vertex));
        m_pGraphic_Dev->Get_Device()->SetIndices(pVertices->Get_IndexBuffer());
        m_pGraphic_Dev->Get_Device()->SetFVF(Vertex::FVF);
        m_pGraphic_Dev->Get_Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 
                                                            pVertices->Get_VerticesCount(), 0, 
                                                            pVertices->Get_PrimCount());
    }
    /////////////////////////////////////////////////

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

void CManagement::Free()
{
    //////////////////////////////
    for (auto pVertices : m_vecVertices)
        SafeRelease(pVertices);
    //////////////////////////////

    SafeRelease(m_pSceneManager);
    SafeRelease(m_pGraphic_Dev);    // Graphice Device�� ��������
}

void CManagement::ReleaseEngine()
{
    // �ڱ⸦ ���� ������ Free()���� RefCnt�� ���ҽ�Ŵ
    if (CManagement::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CManagement");

    // RefCnt�� 0�� ���¿��� Release�� �ؾ� ����� ������
    if (CSceneManager::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CSceneManager");

    if (CGraphic_Device::Destroy_Instance())
        PRINT_LOG(L"Warning", L"Failed To Release CGraphic_Device");
}
#include "..\Headers\Vertices.h"
#include "Grahpic_Device.h"


USING(Engine)

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

CVertices::CVertices()
    : m_pVertexBuffer(nullptr)
    , m_pIndexBuffer(nullptr)
    , m_iVerticesCount(0)
    , m_iPrimCount(0)
    , m_matWorld()
{

}

HRESULT CVertices::ReadyVertices(Vertex vertices[], _uint verticesCount, WORD indices[], _uint indicesCount, _uint primCount)
{
    LPDIRECT3DDEVICE9 pDevice = CGraphic_Device::Get_Instance()->Get_Device();

    if (FAILED(pDevice->CreateVertexBuffer(verticesCount * sizeof(Vertex),
                                           D3DUSAGE_WRITEONLY,
                                           Vertex::FVF,
                                           D3DPOOL_MANAGED,
                                           &m_pVertexBuffer,
                                           0)))
    {
        PRINT_LOG(L"Error", L"Failed To CreateVertexBuffer");
        return E_FAIL;
    };

    if (FAILED(pDevice->CreateIndexBuffer(indicesCount * sizeof(WORD),
                                          D3DUSAGE_WRITEONLY,
                                          D3DFMT_INDEX16,
                                          D3DPOOL_MANAGED,
                                          &m_pIndexBuffer,
                                          0)))
    {
        PRINT_LOG(L"Error", L"Failed To CreateIndexBuffer");
        return E_FAIL;
    };

    Vertex* pVertices;
    m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
    memcpy_s(pVertices, verticesCount * sizeof(Vertex), vertices, verticesCount * sizeof(Vertex));
    m_pVertexBuffer->Unlock();

    WORD* pIndices;
    m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
    memcpy_s(pIndices, indicesCount * sizeof(WORD), indices, indicesCount * sizeof(WORD));
    m_pIndexBuffer->Unlock();

    m_iVerticesCount = verticesCount;
    m_iPrimCount = primCount;

    return S_OK;
}

CVertices* CVertices::Create(Vertex vertices[], _uint verticesCount, WORD indices[], _uint indicesCount, _uint primCount)
{
    CVertices* pInstance = new CVertices;
    if (FAILED(pInstance->ReadyVertices(vertices, verticesCount, indices, indicesCount, primCount)))
    {
        PRINT_LOG(L"Error", L"Failed To Create CVertices");
        SafeRelease(pInstance);
    }

    return pInstance;
}

void CVertices::Free()
{
    SafeRelease(m_pVertexBuffer);
    SafeRelease(m_pIndexBuffer);
}

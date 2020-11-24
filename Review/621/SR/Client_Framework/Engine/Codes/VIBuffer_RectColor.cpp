#include "..\Headers\VIBuffer_RectColor.h"

USING(Engine)

VIBuffer_RectColor::VIBuffer_RectColor(_lpd3dd9 pDevice)
    : VIBuffer(pDevice)
{
}

VIBuffer_RectColor::VIBuffer_RectColor(const VIBuffer_RectColor& other)
    : VIBuffer(other)
{
}

VIBuffer_RectColor* VIBuffer_RectColor::Create(LPDIRECT3DDEVICE9 pDevice)
{   
    VIBuffer_RectColor* pInstance = new VIBuffer_RectColor(pDevice);
    if (FAILED(pInstance->ReadyComponentPrototype()))
    {
        LOG_MSG(L"Error", L"VIBuffer_RectColor Creation has Failed");
        SafeRelease(pInstance);
    }

    return pInstance;
}

Component* VIBuffer_RectColor::Clone(void* pArg)
{
    VIBuffer_RectColor* pClone = new VIBuffer_RectColor(*this);
    if (FAILED(pClone->ReadyComponent(pArg)))
    {
        LOG_MSG(L"Error", L"VIBuffer_RectColor Clone has Failed");
        SafeRelease(pClone);
    }
    return pClone;
}

void VIBuffer_RectColor::Free()
{
    VIBuffer::Free();
}

HRESULT VIBuffer_RectColor::ReadyComponentPrototype()
{
    // 데이터 입력
    m_iVerticesSize = sizeof(VTX_COLOR);
    m_iVerticesCount = 4;
    m_iFVF = FVF_VTX_COLOR;
    m_iPrimCount = 2;

    m_iIndexSize = sizeof(INDEX16);
    m_IndexFormat = D3DFMT_INDEX16;
    //

    if (FAILED(VIBuffer::ReadyComponentPrototype()))
    {
        E_FAIL;
    }

    VTX_COLOR* pVertex = nullptr;
    m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

    pVertex[0].vPosition = D3DXVECTOR3(-1.f, 1.f, 0.f);
    pVertex[0].iColor = D3DCOLOR_ARGB(255, 255, 0, 0);

    pVertex[1].vPosition = D3DXVECTOR3(1.f, 1.f, 0.f);
    pVertex[1].iColor = D3DCOLOR_ARGB(255, 0, 255, 0);

    pVertex[2].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
    pVertex[2].iColor = D3DCOLOR_ARGB(255, 255, 0, 255);

    pVertex[3].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
    pVertex[3].iColor = D3DCOLOR_ARGB(255, 0, 255, 0);
   
    m_pVertexBuffer->Unlock();

    INDEX16* pIndex = nullptr;

    m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

    pIndex[0]._1 = 0;
    pIndex[0]._2 = 1;
    pIndex[0]._3 = 2;

    pIndex[1]._1 = 0;
    pIndex[1]._2 = 2;
    pIndex[1]._3 = 3;

    m_pIndexBuffer->Unlock();

    return S_OK;
}

HRESULT VIBuffer_RectColor::ReadyComponent(void* pArg)
{
    if (FAILED(VIBuffer::ReadyComponent(pArg)))
    {
        return E_FAIL;
    }

    return S_OK;
}

HRESULT VIBuffer_RectColor::Render_VIBuffer()
{
    if (FAILED(VIBuffer::Render_VIBuffer()))
        return E_FAIL;

    /* 장치에게 인덱스버퍼 셋 */
    if (FAILED(m_pDevice->SetIndices(m_pIndexBuffer)))
        return E_FAIL;
    
    return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVerticesCount, 0, m_iPrimCount);
}

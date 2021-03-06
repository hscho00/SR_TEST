#include "VIBuffer_TriColor.h"

USING(Engine)

CVIBuffer_TriColor::CVIBuffer_TriColor(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color)
	: CVIBuffer(pDevice)
	, m_iColor(color)
{

}

CVIBuffer_TriColor::CVIBuffer_TriColor(const CVIBuffer_TriColor& other)
	: CVIBuffer(other)
	, m_iColor(other.m_iColor)
{

}

HRESULT CVIBuffer_TriColor::ReadyComponentPrototype()
{
	//
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iVertexCount = 3;
	m_iFVF = VTX_COLOR::FVF;
	m_iTriCount = 1;

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFormat = D3DFMT_INDEX16;

	//
	if (FAILED(CVIBuffer::ReadyComponentPrototype()))
		return E_FAIL;

	//
	VTX_COLOR* pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = D3DXVECTOR3(0.f, 1.f, 0.f);		// 정점 세팅 시 디폴트 시계 방향으로
	pVertex[0].iColor = m_iColor;							// 디폴트 컬링 설정이 반시계방향 이므로

	pVertex[1].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVertex[1].iColor = m_iColor;

	pVertex[2].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVertex[2].iColor = m_iColor;

	m_pVB->Unlock();

	//
	INDEX16* pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);
	
	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_TriColor::ReadyComponent(void* pArg)
{
	if (FAILED(CVIBuffer::ReadyComponent(pArg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer_TriColor::Render_VIBuffer()
{
	if (FAILED(CVIBuffer::Render_VIBuffer()))
		return E_FAIL;

	/* 도형을 그리는 함수 */
	//return m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iTriCount);
	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);
}

CVIBuffer_TriColor* CVIBuffer_TriColor::Create(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color)
{
	CVIBuffer_TriColor* pInstance = new CVIBuffer_TriColor(pDevice, color);
	if (FAILED(pInstance->ReadyComponentPrototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_TriColor");
		SafeRelease(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_TriColor::Clone(void* pArg)
{
	CVIBuffer_TriColor* pClone = new CVIBuffer_TriColor(*this);
	if (FAILED(pClone->ReadyComponent(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_TriColor");
		SafeRelease(pClone);
	}

	return pClone;
}

void CVIBuffer_TriColor::Free()
{
	CVIBuffer::Free();
}
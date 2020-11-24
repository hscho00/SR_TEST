#include "..\Headers\VIBuffer_QuadColor.h"

USING(Engine)

CVIBuffer_QuadColor::CVIBuffer_QuadColor(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
	, m_iColor(0)
{

}

CVIBuffer_QuadColor::CVIBuffer_QuadColor(const CVIBuffer_QuadColor& other)
	: CVIBuffer(other)
	, m_iColor(other.m_iColor)
{

}

HRESULT CVIBuffer_QuadColor::ReadyComponentPrototype()
{
	//
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iVertexCount = 4;
	m_iFVF = VTX_COLOR::FVF;
	m_iTriCount = 2;

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFormat = D3DFMT_INDEX16;

	//
	if (FAILED(CVIBuffer::ReadyComponentPrototype()))
		return E_FAIL;

	//
	VTX_COLOR* pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = D3DXVECTOR3(1.f, 1.f, 0.f);		// 정점 세팅 시 디폴트 시계 방향으로
	pVertex[0].iColor = m_iColor;							// 디폴트 컬링 설정이 반시계방향 이므로

	pVertex[1].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVertex[1].iColor = m_iColor;

	pVertex[2].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVertex[2].iColor = m_iColor;

	pVertex[3].vPosition = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVertex[3].iColor = m_iColor;

	m_pVB->Unlock();

	//
	INDEX16* pIndex = nullptr;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3;

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_QuadColor::ReadyComponent(void* pArg)
{
	if (FAILED(CVIBuffer::ReadyComponent(pArg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer_QuadColor::Render_VIBuffer()
{
	if (FAILED(CVIBuffer::Render_VIBuffer()))
		return E_FAIL;

	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);
}

CVIBuffer_QuadColor* CVIBuffer_QuadColor::Create(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color)
{
	CVIBuffer_QuadColor* pInstance = new CVIBuffer_QuadColor(pDevice);
	pInstance->m_iColor = color;

	if (FAILED(pInstance->ReadyComponentPrototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_QuadColor");
		SafeRelease(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_QuadColor::Clone(void* pArg)
{
	CVIBuffer_QuadColor* pClone = new CVIBuffer_QuadColor(*this);
	if (FAILED(pClone->ReadyComponent(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_QuadColor");
		SafeRelease(pClone);
	}

	return pClone;
}

void CVIBuffer_QuadColor::Free()
{
	CVIBuffer::Free();
}
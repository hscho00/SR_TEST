#include "VIBuffer_RectColor.h"

USING(Engine)

CVIBuffer_RectColor::CVIBuffer_RectColor(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
{
}

CVIBuffer_RectColor::CVIBuffer_RectColor(const CVIBuffer_RectColor & other)
	: CVIBuffer(other)
{
}

HRESULT CVIBuffer_RectColor::ReadyComponentPrototype()
{

	int nX = 100;
	int nY = 100;
	int iSize = 1;
	int iIndex = 0;
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iVertexCount = (nX + 1) * (nY + 1);
	m_iFVF = FVF_VTX_COLOR;
	m_iTriCount = (nX * nY) * 2;

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFormat = D3DFMT_INDEX16;

	if (FAILED(CVIBuffer::ReadyComponentPrototype()))
		return E_FAIL;

	VTX_COLOR* pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	//pVertex[0].vPosition = D3DXVECTOR3(-1.f, 1.f, 0.f);
	//pVertex[0].iColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	//pVertex[1].vPosition = D3DXVECTOR3(1.f, 1.f, 0.f);
	//pVertex[1].iColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	//pVertex[2].vPosition = D3DXVECTOR3(1.f, -1.f, 0.f);
	//pVertex[2].iColor = D3DCOLOR_ARGB(255, 255, 0, 255);

	//pVertex[3].vPosition = D3DXVECTOR3(-1.f, -1.f, 0.f);
	//pVertex[3].iColor = D3DCOLOR_ARGB(255, 0, 255, 0);	


	for (int Y = 0; Y <= nY; ++Y)
	{
		for (int X = 0; X <= nX; ++X)
		{
			iIndex = X + (Y *(nX + 1));
			pVertex[iIndex].vPosition = D3DXVECTOR3((float)(iSize *X), 0.f, (float)(iSize*Y));
			pVertex[iIndex].iColor = D3DCOLOR_ARGB(255, 255, 255, 0);
		}
	}

	m_pVB->Unlock();

	INDEX16* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);
	int nTemp = 0;
	for (int Y = 0; Y < nY; ++Y)
	{
		for (int X = 0; X < nX; ++X)
		{
			iIndex = X + (Y *(nX + 1));
			pIndex[nTemp*2] = { (WORD)iIndex, (WORD)(iIndex + nX + 1), (WORD)(iIndex + 1) };
			pIndex[nTemp*2 + 1] = { (WORD)(iIndex + nX + 1),(WORD)(iIndex + nX + 2)	, (WORD)(iIndex + 1) };
			++nTemp;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_RectColor::ReadyComponent(void * pArg)
{
	if (FAILED(CVIBuffer::ReadyComponent(pArg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer_RectColor::Render_VIBuffer()
{
	if (FAILED(CVIBuffer::Render_VIBuffer()))
		return E_FAIL;

	/* 장치에게 인덱스버퍼 셋 */
	if (FAILED(m_pDevice->SetIndices(m_pIB)))
		return E_FAIL;

	/* 인덱스를 이용해서 도형을 그리는 함수 */
	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);
}

CVIBuffer_RectColor* CVIBuffer_RectColor::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CVIBuffer_RectColor* pInstance = new CVIBuffer_RectColor(pDevice);
	if (FAILED(pInstance->ReadyComponentPrototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_RectColor");
		SafeRelease(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_RectColor::Clone(void * pArg)
{
	CVIBuffer_RectColor* pClone = new CVIBuffer_RectColor(*this);
	if (FAILED(pClone->ReadyComponent(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_RectColor");
		SafeRelease(pClone);
	}

	return pClone;
}

void CVIBuffer_RectColor::Free()
{
	CVIBuffer::Free();
}

#include "..\Headers\VIBuffer_TerrainColor.h"

USING(Engine)

CVIBuffer_TerrainColor::CVIBuffer_TerrainColor(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color,
												_uint iVertexCountX, _uint iVertexCountZ, _float fVertexInterval)
	: CVIBuffer(pDevice)
	, m_iColor(color)
	, m_iVertexCountX(iVertexCountX)
	, m_iVertexCountZ(iVertexCountZ)
	, m_fVertexInterval(fVertexInterval)
{

}

CVIBuffer_TerrainColor::CVIBuffer_TerrainColor(const CVIBuffer_TerrainColor& other)
	: CVIBuffer(other)
	, m_iColor(other.m_iColor)
	, m_iVertexCountX(other.m_iVertexCountX)
	, m_iVertexCountZ(other.m_iVertexCountZ)
	, m_fVertexInterval(other.m_fVertexInterval)
{

}

HRESULT CVIBuffer_TerrainColor::ReadyComponentPrototype()
{
	if (2 > m_iVertexCountX || 2 > m_iVertexCountZ)
		return E_FAIL;

	//
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iVertexCount = m_iVertexCountX * m_iVertexCountZ;
	m_iFVF = VTX_COLOR::FVF;
	m_iTriCount = (m_iVertexCountX - 1) * (m_iVertexCountZ - 1) * 2;

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFormat = D3DFMT_INDEX16;

	//
	if (FAILED(CVIBuffer::ReadyComponentPrototype()))
		return E_FAIL;

	//
	VTX_COLOR* pVertex = nullptr;
	_uint iVertexIndex = 0;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (_uint z = 0; z < m_iVertexCountZ; ++z)
	{
		for (_uint x = 0; x < m_iVertexCountX; ++x)
		{
			iVertexIndex = z * m_iVertexCountX + x;
			assert(iVertexIndex < m_iVertexCount);

			pVertex[iVertexIndex].vPosition = D3DXVECTOR3(x * m_fVertexInterval, 0.f, z * m_fVertexInterval);
			pVertex[iVertexIndex].iColor = m_iColor;
		}
	}

	m_pVB->Unlock();

	//
	INDEX16* pIndex = nullptr;
	_uint iTriIndex = 0;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (_uint z = 0; z < m_iVertexCountZ - 1; ++z)		// 상단 가장자리에 있는 버텍스는 위로 더 이을 삼각형이 없으므로 -1
	{
		for (_uint x = 0; x < m_iVertexCountX - 1; ++x)	// 우측 가장자리에 있는 버텍스는 옆으로 더 이을 삼각형이 없으므로 -1
		{
			iVertexIndex = z * m_iVertexCountX + x;
			assert(iVertexIndex < m_iVertexCount);

			pIndex[iTriIndex]._1 = iVertexIndex + m_iVertexCountX;
			pIndex[iTriIndex]._2 = iVertexIndex + m_iVertexCountX + 1;
			pIndex[iTriIndex++]._3 = iVertexIndex + 1;

			pIndex[iTriIndex]._1 = iVertexIndex + m_iVertexCountX;
			pIndex[iTriIndex]._2 = iVertexIndex + 1;
			pIndex[iTriIndex++]._3 = iVertexIndex;
		}
	}

	m_pIB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_TerrainColor::ReadyComponent(void* pArg)
{
	if (FAILED(CVIBuffer::ReadyComponent(pArg)))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer_TerrainColor::Render_VIBuffer()
{
	if (FAILED(CVIBuffer::Render_VIBuffer()))
		return E_FAIL;

	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVertexCount, 0, m_iTriCount);
}

CVIBuffer_TerrainColor* CVIBuffer_TerrainColor::Create(LPDIRECT3DDEVICE9 pDevice, D3DCOLOR color,
													_uint iVertexCountX, _uint iVertexCountZ, _float fVertexInterval/*= 1.f*/)
{
	CVIBuffer_TerrainColor* pInstance = new CVIBuffer_TerrainColor(pDevice, color, iVertexCountX, iVertexCountZ, fVertexInterval);
	if (FAILED(pInstance->ReadyComponentPrototype()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CVIBuffer_TerrainColor");
		SafeRelease(pInstance);
	}

	return pInstance;
}

CComponent* CVIBuffer_TerrainColor::Clone(void* pArg)
{
	CVIBuffer_TerrainColor* pClone = new CVIBuffer_TerrainColor(*this);
	if (FAILED(pClone->ReadyComponent(pArg)))
	{
		PRINT_LOG(L"Error", L"Failed To Clone CVIBuffer_TerrainColor");
		SafeRelease(pClone);
	}

	return pClone;
}

void CVIBuffer_TerrainColor::Free()
{
	CVIBuffer::Free();
}
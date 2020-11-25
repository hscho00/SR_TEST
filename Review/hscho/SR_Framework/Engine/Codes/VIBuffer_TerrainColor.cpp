#include "..\Headers\VIBuffer_TerrainColor.h"

USING(Engine)

CVIBuffer_TerrainColor::CVIBuffer_TerrainColor(LPDIRECT3DDEVICE9 pDevice)
	: CVIBuffer(pDevice)
	, m_iCX(0)
	, m_iCY(0)
	, m_iColor(0)
{

}

CVIBuffer_TerrainColor::CVIBuffer_TerrainColor(const CVIBuffer_TerrainColor& other)
	: CVIBuffer(other)
	, m_iCX(other.m_iCX)
	, m_iCY(other.m_iCY)
	, m_iColor(other.m_iCY)
{

}

HRESULT CVIBuffer_TerrainColor::ReadyComponentPrototype()
{
	if (2 > m_iCX || 2 > m_iCY)
		return E_FAIL;

	//
	m_iVertexSize = sizeof(VTX_COLOR);
	m_iVertexCount = m_iCX * m_iCY;
	m_iFVF = VTX_COLOR::FVF;
	m_iTriCount = (m_iCX - 1) * (m_iCY - 1) * 2;

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFormat = D3DFMT_INDEX16;

	//
	if (FAILED(CVIBuffer::ReadyComponentPrototype()))
		return E_FAIL;

	//
	VTX_COLOR* pVertex = nullptr;
	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	for (_uint i = 0; i < m_iCY; ++i)
	{
		for (_uint j = 0; j < m_iCX; ++j)
		{
			pVertex[i * m_iCX + j].vPosition = _vec3((float)j, 0.f, (float)i);
			pVertex[i * m_iCX + j].iColor = m_iColor;

			//cout << i * m_iCX + j << ": "
			//	<< pVertex[i * m_iCX + j].vPosition.x << ", "
			//	<< pVertex[i * m_iCX + j].vPosition.y << ", "
			//	<< pVertex[i * m_iCX + j].vPosition.z << endl;
		}
	}

	m_pVB->Unlock();

	//
	INDEX16* pIndex = nullptr;
	_uint idx = 0;
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	for (_uint i = 0; i < m_iCY - 1; ++i)
	{
		for (_uint j = 0; j < m_iCX - 1; ++j)
		{
			// 0 : i * m_iCX + j
			// 1 : (i * m_iCX + j) + 1
			// 2 : (i + 1) * m_iCX + j
			// 3 : ((i + 1) * m_iCX + j) + 1

			// (0,2,3) (0,3,1) 시계방향

			pIndex[idx]._1 = i * m_iCX + j;
			pIndex[idx]._2 = (i + 1) * m_iCX + j;
			pIndex[idx]._3 = ((i + 1) * m_iCX + j) + 1;
			++idx;

			cout << (idx - 1) << ": "
				<< pIndex[idx - 1]._1 << ", "
				<< pIndex[idx - 1]._2 << ", "
				<< pIndex[idx - 1]._3 << endl;

			pIndex[idx]._1 = i * m_iCX + j;
			pIndex[idx]._2 = ((i + 1) * m_iCX + j) + 1;
			pIndex[idx]._3 = (i * m_iCX + j) + 1;
			++idx;

			cout << (idx - 1) << ": "
				<< pIndex[idx - 1]._1 << ", "
				<< pIndex[idx - 1]._2 << ", "
				<< pIndex[idx - 1]._3 << endl;
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

CVIBuffer_TerrainColor* CVIBuffer_TerrainColor::Create(LPDIRECT3DDEVICE9 pDevice, _uint iCX, _uint iCY, D3DCOLOR color)
{
	CVIBuffer_TerrainColor* pInstance = new CVIBuffer_TerrainColor(pDevice);
	pInstance->m_iCX = iCX;		// 생성자를 더 만드는게 좋지만 귀찮
	pInstance->m_iCY = iCY;
	pInstance->m_iColor = color;

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
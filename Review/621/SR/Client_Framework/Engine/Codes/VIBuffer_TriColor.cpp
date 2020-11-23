#include "VIBuffer_TriColor.h"

USING(Engine)

VIBuffer_TriColor::VIBuffer_TriColor(LPDIRECT3DDEVICE9 pDevice)
	: VIBuffer(pDevice)
{
}

HRESULT VIBuffer_TriColor::ReadyComponentPrototype()
{
	return S_OK;
}

HRESULT VIBuffer_TriColor::ReadyComponent(void* pArg)
{
	return S_OK;
}

HRESULT VIBuffer_TriColor::Render_VIBuffer()
{
	if (FAILED(VIBuffer::Render_VIBuffer()))
		return E_FAIL;
	
	return m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iPrimCount);
}

VIBuffer_TriColor* VIBuffer_TriColor::Create(_lpd3dd9 pDevice, VTX_COLOR vertices[], _uint verticesCount, WORD indices[], _uint indicesCount, _uint primCount)
{
	VIBuffer_TriColor* pInstance = new VIBuffer_TriColor(pDevice);
	if (FAILED(pInstance->ReadyVertices(vertices, verticesCount, indices, indicesCount, primCount)))
	{
		LOG_MSG(L"Error", L"Create Vertices has failed.");
		SafeRelease(pInstance);
	}
	return pInstance;
}

Component* VIBuffer_TriColor::Clone(void* pArg)
{
	VIBuffer_TriColor* pClone = new VIBuffer_TriColor(*this);
	if (FAILED(pClone->ReadyComponent(pArg)))
	{
		LOG_MSG(L"Error", L"Clone CVIBuffer_TriColor has failed.");
		SafeRelease(pClone);
	}

	return pClone;
}

void VIBuffer_TriColor::Free()
{
	VIBuffer::Free();
}

HRESULT VIBuffer_TriColor::ReadyVertices(VTX_COLOR vertices[], _uint verticesCount, WORD indices[], _uint indicesCount, _uint primCount)
{
	m_iVerticesCount = verticesCount;
	m_iVerticesSize = sizeof(vertices) / sizeof(verticesCount);
	m_iIndexSize = sizeof(indices) / sizeof(indicesCount);
	m_iPrimCount = primCount;

	if (FAILED(m_pDevice->CreateVertexBuffer(
		m_iVerticesCount * m_iVerticesSize,
		0,
		m_iFVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		0)))
	{
		LOG_MSG(L"Error", L"Failed To CreateVertexBuffer");
		return E_FAIL;
	}

	if (FAILED(m_pDevice->CreateIndexBuffer(
		indicesCount * m_iIndexSize,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndexBuffer,
		0
	)))
	{
		LOG_MSG(L"Error", L"Failed To CreateIndexBuffer");
		return E_FAIL;
	}

	VTX_COLOR* pVertices;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
	memcpy_s(pVertices, verticesCount * m_iVerticesSize, vertices, verticesCount * sizeof(m_iVerticesSize));
	m_pVertexBuffer->Unlock();

	WORD* pIndices;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndices, 0);
	memcpy_s(pIndices, indicesCount * m_iIndexSize, indices, indicesCount * sizeof(m_iIndexSize));
	m_pIndexBuffer->Unlock();

	m_iVerticesCount = verticesCount;
	m_iPrimCount = primCount;

	return S_OK;
}

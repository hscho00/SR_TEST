#include "..\Headers\Vertices.h"

USING(Engine)

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

Vertices::Vertices(_lpd3dd9 pDevice)
	: Component(pDevice)
	, m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_iVerticesCount(0)
	, m_iPrimCount(0)
{
}

Vertices* Vertices::Create(
	_lpd3dd9 pDevice, 
	Vertex vertices[], 
	_uint verticesCount, 
	WORD indices[], 
	_uint indicesCount, 
	_uint primCount)
{
	Vertices* pInstance = new Vertices(pDevice);
	if (FAILED(pInstance->ReadyVertices(vertices, verticesCount, indices, indicesCount, primCount)))
	{
		LOG_MSG(L"Error", L"Failed To Create Vertices");
		SafeRelease(pInstance);
	}
	return pInstance;
}

Component* Vertices::Clone(void* pArg)
{
	Vertices* pClone = new Vertices(*this);
	if (FAILED(pClone->ReadyComponent(pArg)))
	{
		LOG_MSG(L"Error", L"Vertices clone creation failed.");
		SafeRelease(pClone);
	}
	return pClone;
}

void Vertices::Free()
{
	Component::Free();
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
}

HRESULT Vertices::ReadyComponentPrototype()
{
	return S_OK;
}

HRESULT Vertices::ReadyComponent(void* pArg)
{	
	return S_OK;
}

HRESULT Vertices::ReadyVertices(
	Vertex vertices[],
	_uint verticesCount, 
	WORD indices[], 
	_uint indicesCount, 
	_uint primCount)
{
	if (FAILED(m_pDevice->CreateVertexBuffer(
		verticesCount * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		0)))
	{
		LOG_MSG(L"Error", L"Failed To CreateVertexBuffer");
		return E_FAIL;
	}
	
	if (FAILED(m_pDevice->CreateIndexBuffer(
		indicesCount * sizeof(WORD),
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

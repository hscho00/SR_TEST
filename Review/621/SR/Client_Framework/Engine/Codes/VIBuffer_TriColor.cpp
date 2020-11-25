#include "VIBuffer_TriColor.h"

USING(Engine)

VIBuffer_TriColor::VIBuffer_TriColor(LPDIRECT3DDEVICE9 pDevice)
	: VIBuffer(pDevice)
	, m_iColor(0)
{
}

VIBuffer_TriColor::VIBuffer_TriColor(const VIBuffer_TriColor& other)
	: VIBuffer(other)
	, m_iColor(other.m_iColor)
{
}

HRESULT VIBuffer_TriColor::ReadyComponentPrototype()
{
	//Triangle
	m_iVerticesSize = sizeof(VTX_COLOR);
	m_iVerticesCount = 3;
	m_iFVF = FVF_VTX_COLOR;
	m_iPrimCount = 1;
	m_iIndexSize = 3;
	
	if (FAILED(VIBuffer::ReadyComponentPrototype()))
		return E_FAIL;

	//
	VTX_COLOR* pVertex = nullptr;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	pVertex[0].vPosition = _vector3(0.f, 1.f, 0.f);		// 정점 세팅 시 디폴트 시계 방향으로
	pVertex[0].iColor = m_iColor;							// 디폴트 컬링 설정이 반시계방향 이므로

	pVertex[1].vPosition = _vector3(1.f, -1.f, 0.f);
	pVertex[1].iColor = m_iColor;

	pVertex[2].vPosition = _vector3(-1.f, -1.f, 0.f);
	pVertex[2].iColor = m_iColor;

	m_pVertexBuffer->Unlock();

	WORD* pIndex = nullptr;
	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;

	m_pIndexBuffer->Unlock();
	//


	return S_OK;
}

HRESULT VIBuffer_TriColor::ReadyComponent(void* pArg)
{
	if (FAILED(VIBuffer::ReadyComponent(pArg)))
		return E_FAIL;
	
	return S_OK;
}

HRESULT VIBuffer_TriColor::Render_VIBuffer()
{
	if (FAILED(VIBuffer::Render_VIBuffer()))
		return E_FAIL;
	
	return m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_iPrimCount);
}

VIBuffer_TriColor* VIBuffer_TriColor::Create(_lpd3dd9 pDevice)
{
	VIBuffer_TriColor* pInstance = new VIBuffer_TriColor(pDevice);
	if (FAILED(pInstance->ReadyComponentPrototype()))
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

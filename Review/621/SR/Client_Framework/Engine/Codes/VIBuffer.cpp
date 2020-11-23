#include "..\Headers\VIBuffer.h"

USING(Engine)

VIBuffer::VIBuffer(_lpd3dd9 pDevice)
	: Component(pDevice)
	, m_pVertexBuffer(nullptr)
	, m_pIndexBuffer(nullptr)
	, m_iVerticesCount(0)
	, m_iPrimCount(0)
	, m_iFVF(0)
{
}

VIBuffer::VIBuffer(const VIBuffer& other)
	: Component(other)
	, m_pVertexBuffer(other.m_pVertexBuffer)
	, m_pIndexBuffer(other.m_pIndexBuffer)
	, m_iVerticesCount(other.m_iVerticesCount)
	, m_iPrimCount(other.m_iPrimCount)
	, m_iFVF(other.m_iFVF)
	, m_iVerticesSize(other.m_iVerticesSize)
	, m_iIndexSize(other.m_iIndexSize)

{
}

void VIBuffer::Free()
{
	Component::Free();
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pIndexBuffer);
}

HRESULT VIBuffer::ReadyComponentPrototype()
{
	//if (FAILED(m_pDevice->CreateVertexBuffer(
	//	m_iVerticesSize * m_iVerticesCount, /* 버텍스버퍼가 관리할 배열의 총 사이즈 */
	//	0, /* 0이면 정적버퍼 */
	//	m_iFVF, /* FVF */
	//	D3DPOOL_MANAGED, /* 메모리 보관 방식 */
	//	&m_pVertexBuffer, /* 할당된 버텍스버퍼의 주소를 반환 */
	//	nullptr)))
	//{
	//	return E_FAIL;
	//}

	return S_OK;
}

HRESULT VIBuffer::ReadyComponent(void* pArg)
{	
	return S_OK;
}

HRESULT VIBuffer::Render_VIBuffer()
{
	if (FAILED(m_pDevice->SetStreamSource(0, m_pVertexBuffer, 0, m_iVerticesSize)))
		return E_FAIL;

	if (FAILED(m_pDevice->SetFVF(m_iFVF)))
		return E_FAIL;

	return S_OK;
}


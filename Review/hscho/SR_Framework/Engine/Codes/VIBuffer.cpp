#include "..\Headers\VIBuffer.h"

USING(Engine)

// FVF
const _uint VTX_COLOR::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;	// TEX0 : �ؽ��� ��� X
const _uint VTX_TEXTURE::FVF = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;	// TEXCOORDSIZE2 : 2������ǥ(0���ε���)

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pDevice)
	: CComponent(pDevice)
	, m_pVB(nullptr)
	, m_iVertexSize(0)
	, m_iVertexCount(0)
	, m_iTriCount(0)
	, m_iFVF(0)
	, m_pIB(nullptr)
	, m_iIndexCount(0)
{

}

CVIBuffer::CVIBuffer(const CVIBuffer& other)
	: CComponent(other)
	, m_pVB(other.m_pVB)	// ���� ����. ���� ���۸� �� ���� �ʿ� ����!
	, m_iVertexSize(other.m_iVertexSize)
	, m_iVertexCount(other.m_iVertexCount)
	, m_iTriCount(other.m_iTriCount)
	, m_iFVF(other.m_iFVF)
	, m_pIB(other.m_pIB)
	, m_iIndexCount(other.m_iIndexCount)
{

}

HRESULT CVIBuffer::ReadyComponentPrototype()
{
	if (FAILED(m_pDevice->CreateVertexBuffer(m_iVertexSize * m_iVertexCount, /* ���ؽ����۰� ������ �迭�� �� ������ */
											0, /* dynamic �ƴϸ� �������� */
											m_iFVF, /* FVF */
											D3DPOOL_MANAGED, /* �޸� ���� ���. �������� �� ��� D3DPOOL_MANAGED, ��������(D3DUSAGE_DYNAMIC) �� ��� DEFAULT ����. 
																D3DUSAGE_DYNAMIC �� D3DPOOL_MANAGED�� ȣȯ���� ���� ������, ���ÿ��� ����� �� ����. */
											&m_pVB, /* �Ҵ�� ���ؽ������� �ּҸ� ��ȯ */
											nullptr)))
	{
		PRINT_LOG(L"Error", L"Failed To CreateVertexBuffer");
		return E_FAIL;
	}

	if (FAILED(m_pDevice->CreateIndexBuffer(m_iIndexCount * sizeof(WORD),
											0,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&m_pIB,
											nullptr)))
	{
		PRINT_LOG(L"Error", L"Failed To CreateIndexBuffer");
		return E_FAIL;
	};

	return S_OK;
}

HRESULT CVIBuffer::ReadyComponent(void* pArg)
{
	return S_OK;
}

HRESULT CVIBuffer::Render_VIBuffer()
{
	/* ��ġ���� ���ؽ����� ���� */
	if (FAILED(m_pDevice->SetStreamSource(0, m_pVB, 0, m_iVertexSize))) // (�� ��° ����?, ��������, ������, ���� ���� ������)
		return E_FAIL;

	/* ��ġ���� �ε������� ���� */
	if (FAILED(m_pDevice->SetIndices(m_pIB)))
		return E_FAIL;

	/* ��ġ���� FVF ���� */
	if (FAILED(m_pDevice->SetFVF(m_iFVF)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
	/* �θ��� free */
	CComponent::Free();

	/* �ڽ��� ���ҽ� ���� */
	SafeRelease(m_pIB);
	SafeRelease(m_pVB);
}

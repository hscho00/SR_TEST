#include "..\Headers\VIBuffer.h"

USING(Engine)

// FVF
const _uint VTX_COLOR::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;	// TEX0 : 텍스쳐 사용 X
const _uint VTX_TEXTURE::FVF = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;	// TEXCOORDSIZE2 : 2차원좌표(0번인덱스)

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
	, m_pVB(other.m_pVB)	// 얕은 복사. 정점 버퍼를 또 만들 필요 없다!
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
	if (FAILED(m_pDevice->CreateVertexBuffer(m_iVertexSize * m_iVertexCount, /* 버텍스버퍼가 관리할 배열의 총 사이즈 */
											0, /* dynamic 아니면 정적버퍼 */
											m_iFVF, /* FVF */
											D3DPOOL_MANAGED, /* 메모리 보관 방식. 정적버퍼 쓸 경우 D3DPOOL_MANAGED, 동적버퍼(D3DUSAGE_DYNAMIC) 쓸 경우 DEFAULT 쓰자. 
																D3DUSAGE_DYNAMIC 와 D3DPOOL_MANAGED는 호환성이 없기 때문에, 동시에는 사용할 수 없다. */
											&m_pVB, /* 할당된 버텍스버퍼의 주소를 반환 */
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
	/* 장치에게 버텍스버퍼 전달 */
	if (FAILED(m_pDevice->SetStreamSource(0, m_pVB, 0, m_iVertexSize))) // (몇 번째 소켓?, 정점버퍼, 오프셋, 정점 개당 사이즈)
		return E_FAIL;

	/* 장치에게 인덱스버퍼 전달 */
	if (FAILED(m_pDevice->SetIndices(m_pIB)))
		return E_FAIL;

	/* 장치에게 FVF 전달 */
	if (FAILED(m_pDevice->SetFVF(m_iFVF)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
	/* 부모의 free */
	CComponent::Free();

	/* 자식의 리소스 해제 */
	SafeRelease(m_pIB);
	SafeRelease(m_pVB);
}

#include "..\Headers\VIBuffer.h"

USING(Engine)

CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
{
}

HRESULT CVIBuffer::ReadyComponentPrototype()
{
	if (FAILED(m_pDevice->CreateVertexBuffer(
		m_iVertexSize * m_iVertexCount,
		0,
		m_iFVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		nullptr)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CVIBuffer::ReadyComponent(void * pArg)
{
	return E_NOTIMPL;
}

HRESULT CVIBuffer::Render_VIBuffer()
{
	if (FAILED(m_pDevice->SetStreamSource(0, m_pVB, 0, m_iVertexCount)))
		return E_FAIL;

	if (FAILED(m_pDevice->SetFVF(m_iFVF)))
		return E_FAIL;
	return S_OK;
}

void CVIBuffer::Free()
{
	CComponent::Free();

	SafeRelease(m_pVB);
}



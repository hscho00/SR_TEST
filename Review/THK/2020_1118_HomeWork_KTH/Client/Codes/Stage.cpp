#include "stdafx.h"
#include "..\Headers\Stage.h"


CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
	: CScene(pDevice)
{
}

HRESULT CStage::ReadyScene()
{
	CScene::ReadyScene();

	PRINT_LOG(L"Stage", L"Stage");

	m_pDevice->CreateVertexBuffer(
		8 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);
	m_pDevice->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);

	ColorVertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = ColorVertex(-1.f, -1.f, -1.f,D3DCOLOR_XRGB(255,0,0));
	vertices[1] = ColorVertex(-1.f, 1.f, -1.f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[2] = ColorVertex(1.f, 1.f, -1.f, D3DCOLOR_XRGB(255, 0, 255));
	vertices[3] = ColorVertex(1.f, -1.f, -1.f, D3DCOLOR_XRGB(90, 255, 0));
	vertices[4] = ColorVertex(-1.f, -1.f, 1.f, D3DCOLOR_XRGB(80, 0, 255));
	vertices[5] = ColorVertex(-1.f, 1.f, 1.f, D3DCOLOR_XRGB(255, 255, 0));
	vertices[6] = ColorVertex(1.f, 1.f, 1.f, D3DCOLOR_XRGB(255, 52, 5));
	vertices[7] = ColorVertex(1.f, -1.f, 1.f, D3DCOLOR_XRGB(3, 123, 125));

	VB->Unlock();

	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	indices[6] = 4;
	indices[7] = 6;
	indices[8] = 5;
	indices[9] = 4;
	indices[10] = 7;
	indices[11] = 6;

	indices[12] = 4;
	indices[13] = 5;
	indices[14] = 1;
	indices[15] = 4;
	indices[16] = 1;
	indices[17] = 0;

	indices[18] = 3;
	indices[19] = 2;
	indices[20] = 6;
	indices[21] = 3;
	indices[22] = 6;
	indices[23] = 7;

	indices[24] = 1;
	indices[25] = 5;
	indices[26] = 6;
	indices[27] = 1;
	indices[28] = 6;
	indices[29] = 2;

	indices[30] = 4;
	indices[31] = 0;
	indices[32] = 3;
	indices[33] = 4;
	indices[34] = 3;
	indices[35] = 7;

	IB->Unlock();

	D3DXVECTOR3 position(0.f, 0.f, -5.f);
	D3DXVECTOR3 target(0.f, 0.f, 0.f);
	D3DXVECTOR3 up(0.f, 1.f, 0.f);
	D3DXMATRIX V;

	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	m_pDevice->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)WINCX / (float)WINCY,
		1.0f,
		1000.0f);

	m_pDevice->SetTransform(D3DTS_PROJECTION, &proj);

	//m_pDevice->SetRenderState(D3DRS_FILLMODE, d3dfill_);

	return S_OK;
}

_uint CStage::UpdateScene()
{
	CScene::UpdateScene();

	if (m_pDevice)
	{
		D3DXMATRIX Rx, Ry;

		D3DXMatrixRotationX(&Rx, 3.14f / 4.0f);

		static float y = 0.f;
		D3DXMatrixRotationY(&Ry, y);
		y += 0.005f;

		if (y >= 6.28f)
			y = 0.f;

		D3DXMATRIX p = Rx* Ry;

		m_pDevice->SetTransform(D3DTS_WORLD, &p);


		m_pDevice->Clear(0, 0,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_ARGB(255, 0, 0, 0), 1.0f, 0);
		m_pDevice->BeginScene();
		m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		m_pDevice->SetStreamSource(0, VB, 0, sizeof(ColorVertex));
		m_pDevice->SetIndices(IB);
		m_pDevice->SetFVF(ColorVertex::FVF);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0, 0, 8, 0, 12);

		m_pDevice->EndScene();
		m_pDevice->Present(0, 0, 0, 0);
	}


	return _uint();
}

_uint CStage::LateUpdateScene()
{
	CScene::LateUpdateScene();

	return _uint();
}

CStage * CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	CStage* pInstance = new CStage(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CStage");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void CStage::Free()
{
	CScene::Free();
}

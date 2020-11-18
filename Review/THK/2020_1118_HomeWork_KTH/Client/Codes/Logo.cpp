#include "stdafx.h"
#include "..\Headers\Logo.h"
#include "Stage.h"


CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
	: CScene(pDevice)
{
}

HRESULT CLogo::ReadyScene()
{
	CScene::ReadyScene();

	PRINT_LOG(L"Logo", L"Logo");

	//m_pDevice->CreateVertexBuffer(
	//	3 * sizeof(Vertex),
	//	D3DUSAGE_WRITEONLY,
	//	Vertex::FVF,
	//	D3DPOOL_MANAGED,
	//	&VB, 
	//	0);
	//m_pDevice->CreateIndexBuffer(
	//	3 * sizeof(WORD),
	//	D3DUSAGE_WRITEONLY,
	//	D3DFMT_INDEX16,
	//	D3DPOOL_MANAGED,
	//	&IB,
	//	0);

	//Vertex* vertices;
	//VB->Lock(0, 0, (void**)&vertices, 0);

	//vertices[0] = Vertex(-1.f, 0.f, -1.f);
	//vertices[1] = Vertex(1.f, 0.f, -1.f);
	//vertices[2] = Vertex(0.f, 1.f, -1.f);
	//vertices[3] = Vertex(1.f, -1.f, -1.f);
	//vertices[4] = Vertex(-1.f, -1.f, 1.f);
	//vertices[5] = Vertex(-1.f, 1.f, 1.f);
	//vertices[6] = Vertex(1.f, 1.f, 1.f);
	//vertices[7] = Vertex(1.f, -1.f, 1.f);

	m_pDevice->CreateVertexBuffer(
		3 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&Triangle, 
		0);

	ColorVertex* v;
	Triangle->Lock(0, 0, (void**)&v, 0);

	v[2] = ColorVertex(-1.f, 0.f, 2.f, D3DCOLOR_XRGB(255, 0, 0));
	v[1] = ColorVertex(1.f, 0.f, 2.f, D3DCOLOR_XRGB(0, 255, 0));
	v[0] = ColorVertex(0.f, 1.f, 2.f, D3DCOLOR_XRGB(0, 255, 255));
	 
	Triangle->Unlock();

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
		1000.f);

	m_pDevice->SetTransform(D3DTS_PROJECTION, &proj);
	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);


	//VB->Unlock();

	//WORD* indices = 0;
	//IB->Lock(0, 0, (void**)&indices, 0);

	//indices[0] = 2;
	//indices[1] = 1;
	//indices[2] = 0;
	//indices[3] = 0;
	//indices[4] = 2;
	//indices[5] = 3;

	//indices[6] = 4;
	//indices[7] = 6;
	//indices[8] = 5;
	//indices[9] = 4;
	//indices[10] = 7;
	//indices[11] = 6;

	//indices[12] = 4;
	//indices[13] = 5;
	//indices[14] = 1;
	//indices[15] = 4;
	//indices[16] = 1;
	//indices[17] = 0;

	//indices[18] = 3;
	//indices[19] = 2;
	//indices[20] = 6;
	//indices[21] = 3;
	//indices[22] = 6;
	//indices[23] = 7;

	//indices[24] = 1;
	//indices[25] = 5;
	//indices[26] = 6;
	//indices[27] = 1;
	//indices[28] = 6;
	//indices[29] = 2;

	//indices[30] = 4;
	//indices[31] = 0;
	//indices[32] = 3;
	//indices[33] = 4;
	//indices[34] = 3;
	//indices[35] = 7;

	/*IB->Unlock();

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

	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);*/

	return S_OK;
}

_uint CLogo::UpdateScene()
{
	CScene::UpdateScene();


	if (m_pDevice)
	{
		//D3DXMATRIX Rx, Ry;

		//D3DXMatrixRotationX(&Rx, 3.14f / 4.0f);

		//static float y = 0.f;
		//D3DXMatrixRotationY(&Ry, y);
		//y += 0.001f;

		//if (y >= 6.28f)
		//	y = 0.f;

		//D3DXMATRIX p = Rx* Ry;

		//D3DXMATRIX x;
		//

		//D3DXMatrixScaling(&x, 3.f, 3.f, 1.f);
		//

		//m_pDevice->SetTransform(D3DTS_WORLD, &x);
		//m_pDevice->Clear(0, 0,
		//	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//	D3DCOLOR_ARGB(255,255,255,255), 1.0f, 0);
		//m_pDevice->BeginScene();

		//m_pDevice->SetStreamSource(0, VB, 0, sizeof(Vertex));
		//m_pDevice->SetIndices(IB);
		//m_pDevice->SetFVF(Vertex::FVF);
		//m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		//	0, 0, 3, 0, 1);

		//m_pDevice->EndScene();
		//m_pDevice->Present(0, 0, 0, 0);


		

		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0,0,0), 1.f, 0);
		m_pDevice->BeginScene();

		m_pDevice->SetStreamSource(0, Triangle, 0,sizeof(ColorVertex));
		m_pDevice->SetFVF(ColorVertex::FVF);

		D3DXMATRIX p, t;
		D3DXMatrixScaling(&p, 3.f, 3.f, 1.f);
		D3DXMatrixTranslation(&t, -2.f, 0.f, 0.f);
		World = p * t;

		m_pDevice->SetTransform(D3DTS_WORLD, &World);
		m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		D3DXMatrixTranslation(&World, 2.f, 0.f, 0.f);
		m_pDevice->SetTransform(D3DTS_WORLD, &World);
		m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		m_pDevice->EndScene();
		m_pDevice->Present(0, 0, g_hWnd, 0);
	}




	return _uint();
}

_uint CLogo::LateUpdateScene()
{
	CScene::LateUpdateScene();

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		CManagement* pManagement = CManagement::Get_Instance();
		if (nullptr == pManagement)
			return 0;

		if (FAILED(pManagement->SetUpCurrentScene((_int)ESceneID::Stage,
			CStage::Create(m_pDevice))))
		{
			PRINT_LOG(L"Error", L"Failed To SetUpCurrentScene");
			return 0;
		}

		return CHANGE_SCNENE;
	}
	return _uint();
}

CLogo * CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	CLogo* pInstance = new CLogo(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Logo");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void CLogo::Free()
{
	CScene::Free();
}

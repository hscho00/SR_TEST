#include "stdafx.h"
#include "..\Headers\Logo.h"
#include "Stage.h"

Logo::Logo(LPDIRECT3DDEVICE9 pDevice)
	: Scene(pDevice)
{
}


Logo* Logo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	Logo* pInstance = new Logo(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		LOG_MSG(L"Error", L"Preparation of LogoScene has Failed");
		SafeRelease(pInstance);
	}

	return pInstance;
}

HRESULT Logo::ReadyScene()
{
	Scene::ReadyScene();

	//LOG_MSG(L"Logo", L"Logo");

	m_pDevice->CreateVertexBuffer
	(
		8 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0
	);

	m_pDevice->CreateIndexBuffer
	(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0
	);

	// 큐브 데이터로 버퍼를 채움
	Vertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-1.f,	-1.f,	-1.f);
	vertices[1] = Vertex(-1.f,	1.f,	-1.f);
	vertices[2] = Vertex(1.f,	1.f,	-1.f);
	vertices[3] = Vertex(1.f,	-1.f,	-1.f);
	vertices[4] = Vertex(-1.f,	-1.f,	1.f);
	vertices[5] = Vertex(-1.f,	1.f,	1.f);
	vertices[6] = Vertex(1.f,	1.f,	1.f);
	vertices[7] = Vertex(1.f,	-1.f,	1.f);

	VB->Unlock();

	// 입방체의 삼각형들을 정의한다.

	SHORT* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);

	// 전면
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	//후면
	indices[6]	=	4;
	indices[7]	=	6;
	indices[8]	=	5;
	indices[9]	=	4;
	indices[10]	=	7;
	indices[11] =	6;

	//왼쪽 측면
	indices[12] = 4;
	indices[13] = 5;
	indices[14] = 1;
	indices[15] = 4;
	indices[16] = 1;
	indices[17] = 0;

	//오른쪽 측면
	indices[18] = 3;
	indices[19] = 2;
	indices[20] = 6;
	indices[21] = 3;
	indices[22] = 6;
	indices[23] = 7;

	//상단
	indices[24] = 1;
	indices[25] = 5;
	indices[26] = 6;
	indices[27] = 1;
	indices[28] = 6;
	indices[29] = 2;

	//하단
	indices[30] = 4;
	indices[31] = 0;
	indices[32] = 3;
	indices[33] = 4;
	indices[34] = 3;
	indices[35] = 7;

	IB->Unlock();

	// 카메라의 위치와 방향 조정
	_vector3	position(0.f, 0.f, -5.f);
	_vector3	target(0.f, 0.f, 0.f);
	_vector3	up(0.f, 1.f, 0.f);
	_matrix		v;
	D3DXMatrixLookAtLH(&v, &position, &target, &up);
	m_pDevice->SetTransform(D3DTS_VIEW, &v);
	// 투영 행렬 지정
	_matrix proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		float(WINCX) / float(WINCY),
		1.f,
		1000.f);

	m_pDevice->SetTransform(D3DTS_PROJECTION, &proj);

	// 렌더 상태를 지정한다.
	m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	return S_OK;
}

_uint Logo::UpdateScene()
{
	Scene::UpdateScene();
	
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		Management* pManagement = Management::Get_Instance();
		if (nullptr == pManagement)
			return 0;

		if (FAILED(pManagement->SetUpCurrentScene((_int)SceneID::Stage,
			Stage::Create(m_pDevice))))
		{
			LOG_MSG(L"Error", L"SetUpCurrentScene has Failed");
			return 0;
		}

		return CHANGE_SCNENE;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_cube_position.x -= 0.01f;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_cube_position.x += 0.01f;
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_cube_position.y += 0.01f;
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_cube_position.y -= 0.01f;
	}
	else if (GetAsyncKeyState('T') & 0x8000)
	{
		m_cube_position.z += 0.01f;
	}
	else if (GetAsyncKeyState('G') & 0x8000)
	{
		m_cube_position.z -= 0.01f;
	}

	return _uint();
}

_uint Logo::LateUpdateScene()
{
	Scene::LateUpdateScene();


	if (m_pDevice)
	{
		// Render 
		// 회전
		_matrix rotation_x, rotation_y, mat_trans;

		//m_cube_rotation_y += 0.005f;
		//m_cube_rotation_x += 0.005f;

		//if (m_cube_rotation_y >= 6.28f)
		//	m_cube_rotation_y = 0.f;

		// x축으로 45도 회전

		// 프레임 당 y 회전

	/*	D3DXMatrixRotationX(&rotation_x, m_cube_rotation_x);*/
		D3DXMatrixRotationY(&rotation_y, m_cube_rotation_y);
		D3DXMatrixTranslation(&mat_trans, m_cube_position.x, m_cube_position.y, m_cube_position.z);


		_matrix world = rotation_y * mat_trans /** rotation_y*/;
		m_pDevice->SetTransform(D3DTS_WORLD, &world);

		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff/*D3DCOLOR_ARGB(255,0,0,0)*/, 1.f, 0);

		m_pDevice->BeginScene();

		m_pDevice->SetStreamSource(0, VB, 0, sizeof(Vertex));
		m_pDevice->SetIndices(IB);
		m_pDevice->SetFVF(Vertex::FVF);
		m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);

		m_pDevice->EndScene();
		m_pDevice->Present(0, 0, g_hWnd, 0);
	}

	return _uint();
}

void Logo::Free()
{
	Scene::Free();
	VB->Release();
	IB->Release();
	m_pDevice->Release();

}

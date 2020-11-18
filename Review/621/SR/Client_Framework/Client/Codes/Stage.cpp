#include "stdafx.h"
#include "..\Headers\Stage.h"

Stage::Stage(LPDIRECT3DDEVICE9 pDevice)
    : Scene(pDevice)
{
}

HRESULT Stage::ReadyScene()
{
    Scene::ReadyScene();

	m_pDevice->CreateVertexBuffer(
		3 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF,
		D3DPOOL_MANAGED,
		&Triangle,
		0
	);

	ColorVertex* v;
	Triangle->Lock(0, 0, (void**)&v, 0);
	v[0] = ColorVertex(	-1.f, 0.f, 2.f, D3DCOLOR_XRGB(255, 0, 0));
	v[1] = ColorVertex(0.f, 1.f, 2.f, D3DCOLOR_XRGB(0, 255, 0));
	v[2] = ColorVertex(1.f, 0.f, 2.f, D3DCOLOR_XRGB(0, 0, 255));

	Triangle->Unlock();

	// 투영 매트릭스 지정
	_matrix	proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f,
		(float)WINCX / (float)WINCY,
		1.f,
		1000.f
	);
	m_pDevice->SetTransform(D3DTS_PROJECTION, &proj);

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

_uint Stage::UpdateScene()
{
    Scene::UpdateScene();

    return _uint();
}

_uint Stage::LateUpdateScene()
{
    Scene::LateUpdateScene();

	if (m_pDevice)
	{
		m_pDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			0xffffffff/*D3DCOLOR_XRGB(255, 255, 255, 255)*/, 1.f, 0);
		m_pDevice->BeginScene();

		m_pDevice->SetFVF(ColorVertex::FVF);
		m_pDevice->SetStreamSource(0, Triangle, 0, sizeof(ColorVertex));
	
		// 플랫 쉐이딩으로 화면 왼쪽에 삼각형을 그린다.

		D3DXMatrixTranslation(&world, -1.25f, 0.f, 0.f);
		m_pDevice->SetTransform(D3DTS_WORLD, &world);
		m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		// 그라우스 쉐이딩으로 화면 오른쪽에 삼각형
		D3DXMatrixTranslation(&world, 1.25f, 0.f, 0.f);
		m_pDevice->SetTransform(D3DTS_WORLD, &world);
		m_pDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

		m_pDevice->EndScene();
		m_pDevice->Present(0, 0, g_hWnd, 0);

	}

    return _uint();
}

Stage* Stage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	Stage* pInstance = new Stage(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		LOG_MSG(L"Error", L"Preparation of StageScene has Failed");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void Stage::Free()
{
	Scene::Free();

	m_pDevice->Release();
}

#include "stdafx.h"
#include "..\Headers\Stage.h"

#include "Vertices.h"


CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
    : CScene(pDevice)
{

}

HRESULT CStage::ReadyScene()
{
    // 오버라이딩 시 부모의 함수를 꼭 호출해 주자
    CScene::ReadyScene();

    PRINT_LOG(L"Stage", L"Stage");

    /////////////////////////////////////////////////
    //
    _vec3 cameraPos(0.f, 0.f, -5.f);
    _vec3 targetPos(0.f, 0.f, 0.f);
    _vec3 up(0.f, 1.f, 0.f);
    _matrix viewMat;
    D3DXMatrixLookAtLH(&viewMat, &cameraPos, &targetPos, &up);
    m_pDevice->SetTransform(D3DTS_VIEW, &viewMat);

    //
    _matrix projMat;
    D3DXMatrixPerspectiveFovLH(&projMat,
                                D3DX_PI * 0.5f,
                                (float)WINCX / (float)WINCY,
                                1.f,
                                1000.f);
    m_pDevice->SetTransform(D3DTS_PROJECTION, &projMat);

    //
    m_pDevice->SetRenderState(D3DRS_LIGHTING, false);

    //
    CVertices* pVertex = nullptr;
    _matrix matScale, matTrans, matWorld;
    Vertex vertices[4] = {};
    WORD indices[6] = {};

    std::vector<CVertices*>& vecVertices = CManagement::Get_Instance()->Get_VecVertices();
    vecVertices.reserve(2);

    vertices[0] = Vertex(-1.f, -1.f, 0.f, D3DCOLOR_XRGB(255, 0, 0));
    vertices[1] = Vertex(0.f, 1.f, 0.f, D3DCOLOR_XRGB(0, 0, 255));
    vertices[2] = Vertex(1.f, -1.f, 0.f, D3DCOLOR_XRGB(255, 255, 0));
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
    D3DXMatrixTranslation(&matTrans, -3.f, 1.f, 0.f);
    matWorld = matScale * matTrans;
    pVertex = CVertices::Create(vertices, 3, indices, 4, 1);
    assert(pVertex);
    pVertex->Set_MatWorld(matWorld);
    vecVertices.push_back(pVertex);

    vertices[0] = Vertex(-1.f, -1.f, 0.f, D3DCOLOR_XRGB(0, 255, 0));
    vertices[1] = Vertex(-1.f, 1.f, 0.f, D3DCOLOR_XRGB(255, 0, 255));
    vertices[2] = Vertex(1.f, 1.f, 0.f, D3DCOLOR_XRGB(255, 255, 255));
    vertices[3] = Vertex(1.f, -1.f, 0.f, D3DCOLOR_XRGB(0, 255, 255));
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;
    indices[3] = 0;
    indices[4] = 2;
    indices[5] = 3;
    D3DXMatrixScaling(&matScale, 2.f, 2.f, 1.f);
    D3DXMatrixTranslation(&matTrans, 3.f, -1.f, 0.f);
    matWorld = matScale * matTrans;
    pVertex = CVertices::Create(vertices, 4, indices, 6, 2);
    assert(pVertex);
    pVertex->Set_MatWorld(matWorld);
    vecVertices.push_back(pVertex);
    /////////////////////////////////////////////////

    return S_OK;
}

_uint CStage::UpdateScene()
{
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::UpdateScene();

	return NO_EVENT;
}

_uint CStage::LateUpdateScene()
{
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::LateUpdateScene();

	return NO_EVENT;
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	if (nullptr == pDevice)
		return nullptr;

	CStage* pInstance = new CStage(pDevice);
	if (FAILED(pInstance->ReadyScene()))
	{
		PRINT_LOG(L"Error", L"Failed To Create Stage");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void CStage::Free()
{
	// 오버라이딩 시 부모의 함수를 꼭 호출해 주자
	CScene::Free();
}

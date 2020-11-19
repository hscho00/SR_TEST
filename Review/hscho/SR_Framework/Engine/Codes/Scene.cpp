#include "..\Headers\Scene.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	, m_iSceneIndex(-1)
{
	// 외부에서 가져온 포인터가 누군가 소유한 포인터다,
	// 그 포인터를 자기도 소유한다(멤버변수로), 면 AddRef() 해주자
	SafeAddRef(pDevice);
}

HRESULT CScene::ReadyScene()
{
	return S_OK;
}

_uint CScene::UpdateScene()
{
	return NO_EVENT;
}

_uint CScene::LateUpdateScene()
{
	return NO_EVENT;
}

void CScene::Free()
{
	// AddRef() 했으면 Release()도 해주자
	SafeRelease(m_pDevice);
}

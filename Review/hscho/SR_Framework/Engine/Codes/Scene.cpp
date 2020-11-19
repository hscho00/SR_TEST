#include "..\Headers\Scene.h"

USING(Engine)

CScene::CScene(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	, m_iSceneIndex(-1)
{
	// �ܺο��� ������ �����Ͱ� ������ ������ �����ʹ�,
	// �� �����͸� �ڱ⵵ �����Ѵ�(���������), �� AddRef() ������
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
	// AddRef() ������ Release()�� ������
	SafeRelease(m_pDevice);
}

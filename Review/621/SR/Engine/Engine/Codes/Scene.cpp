#include "Scene.h"

USING(Engine)

Scene::Scene(_LPD3DD9 pDevice)
	: m_pDevice(pDevice)
{
	SafeAddRef(pDevice);
}

HRESULT Scene::ReadyScene()
{
	return S_OK;
}

_uint Scene::UpdateScene()
{
	return _uint();
}

_uint Scene::LateUpdateScene()
{
	return _uint();
}

void Scene::Free()
{
	SafeRelease(m_pDevice);
}

#include "..\Headers\GameObject.h"

//////////////
#include "Vertices.h"
//////////////

USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	, m_bUsing(true)
	, m_bDead(false)
	, m_bDraw(true)
	/////////////////////////////
	, m_vPos()
	, m_pVertices(nullptr)
	, m_matWorld()
	/////////////////////////////
{
	assert(m_pDevice);
	SafeAddRef(m_pDevice);
}

HRESULT CGameObject::ReadyGameObjectPrototype()
{
	return S_OK;
}

HRESULT CGameObject::ReadyGameObject(void* pArg)
{
	return S_OK;
}

_uint CGameObject::UpdateGameObject(float fDeltaTime)
{
	if (m_bDead)
		return OBJ_DEAD;

	return NO_EVENT;
}

_uint CGameObject::LateUpdateGameObject(float fDeltaTime)
{
	return NO_EVENT;
}

HRESULT CGameObject::RenderGameObject()
{
	return S_OK;
}

void CGameObject::Free()
{
	/////////////////////////////
	SafeRelease(m_pVertices);
	/////////////////////////////

	SafeRelease(m_pDevice);
}
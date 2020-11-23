#include "..\Headers\GameObject.h"

#include "Management.h"

USING(Engine)

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
	, m_bUsing(true)
	, m_bDead(false)
	, m_bDraw(true)
	/////////////////////////////
	, m_vPos()
	, m_fAngle(0.f)
	, m_matWorld()
	/////////////////////////////
{
	assert(m_pDevice);
	SafeAddRef(m_pDevice);
}

CGameObject::CGameObject(const CGameObject& other)
	: m_pDevice(other.m_pDevice)
	, m_bUsing(other.m_bUsing)
	, m_bDead(other.m_bDead)
	, m_bDraw(other.m_bDraw)
	/////////////////////////////
	, m_vPos(other.m_vPos)
	, m_fAngle(other.m_fAngle)
	, m_matWorld(other.m_matWorld)
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

HRESULT CGameObject::AddComponent(_int iSceneIndex, const wstring& PrototypeTag, const wstring& ComponentTag, CComponent** ppComponent/*= nullptr*/, void* pArg/*= nullptr*/)
{
	auto pManagement = CManagement::Get_Instance();
	assert(pManagement);

	CComponent* pClone = pManagement->CloneComponentPrototype(iSceneIndex, PrototypeTag, pArg);
	if (nullptr == pClone)
		return E_FAIL;

	m_Components.insert(make_pair(ComponentTag, pClone));

	if (ppComponent)
	{
		*ppComponent = pClone;
		SafeAddRef(pClone);
	}

	return S_OK;
}

void CGameObject::Free()
{
	for (auto& Pair : m_Components)
	{
		SafeRelease(Pair.second);
	}
	m_Components.clear();

	SafeRelease(m_pDevice);
}
#include "stdafx.h"
#include "..\Headers\Player.h"

Player::Player(_lpd3dd9 pDevice)
	: GameObject(pDevice)
	, m_vAngle(0.f,0.f,0.f)
{
}

Player::Player(const Player& other)
	: GameObject(other)
	, m_vAngle(other.m_vAngle)
{
}

HRESULT Player::ReadyGameObjectPrototype()
{
	if (FAILED(GameObject::ReadyGameObjectPrototype()))
		return E_FAIL;

	m_vPos = _vector3(0.f, 0.f, 0.f);

	return S_OK;
}

HRESULT Player::ReadyGameObject(void* _pArg /*= nullptr*/)	// clone ÀÇ ·¹µð...
{
	if (FAILED(GameObject::ReadyGameObject(_pArg)))
	{
		return E_FAIL;
	}

	if (FAILED(AddComponent()))
	{
		return E_FAIL;
	}

	return S_OK;
}

_uint Player::UpdateGameObject(DOUBLE _fDeltaTime)
{
	GameObject::UpdateGameObject(_fDeltaTime);	
	
	return _uint();
}

_uint Player::LateUpdateGameObject(DOUBLE _fDeltaTime)
{
	GameObject::LateUpdateGameObject(_fDeltaTime);
	
	auto pManagement = Management::Get_Instance();
	if (nullptr == pManagement)
	{
		return 0;
	}

	if (FAILED(pManagement->AddGameObjectInRenderer(RenderID::NOALPHA, this)))
		return 0;
	return _uint();
}

HRESULT Player::RenderGameObject()
{
	if (FAILED(GameObject::RenderGameObject()))
	{
		return E_FAIL;
	}
	
	if (FAILED(m_pVIBufferCom->Render_VIBuffer()))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Player::AddComponent()	
{
	/* Com_VIBuffer */
	if (FAILED(GameObject::AddComponent(
		(_int)SceneID::Static,
		L"Component_VIBuffer_RectColor",
		L"Com_VIBuffer",
		(Component**)&m_pVIBufferCom
	)))
	{
		return E_FAIL;
	}

	// 
	
	return S_OK;
}

Player* Player::Create(_lpd3dd9 pDevice)
{
	if (nullptr == pDevice) { return nullptr; }
	
	Player* pInstance = new Player(pDevice);
	if (FAILED(pInstance->ReadyGameObjectPrototype()))
	{
		LOG_MSG(L"Error", L"Player Create has Failed");
		SafeRelease(pInstance);
	}

	return pInstance;
}

GameObject* Player::Clone(void* _pArg/* = nullptr*/)
{
	Player* pClone = new Player(*this);	

	if (FAILED(pClone->ReadyGameObject(_pArg)))
	{
		LOG_MSG(L"Error", L"Player clone creation failed.");
		SafeRelease(pClone);
	}

	return pClone;
}

void Player::Free()
{
	GameObject::Free();

	SafeRelease(m_pVIBufferCom);
}

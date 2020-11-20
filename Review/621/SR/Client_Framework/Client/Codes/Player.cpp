#include "stdafx.h"
#include "..\Headers\Player.h"

Player::Player(_lpd3dd9 pDevice)
	: GameObject(pDevice)
{
}

HRESULT Player::ReadyGameObjectPrototype()
{
	if (FAILED(GameObject::ReadyGameObjectPrototype()))
		return E_FAIL;
	
	return S_OK;
}

HRESULT Player::ReadyGameObject(void* _pArg /*= nullptr*/)
{
	if (FAILED(GameObject::ReadyGameObject(_pArg)))
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

		return pInstance;
	}
}

GameObject* Player::Clone(void* _pArg = nullptr)
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
}

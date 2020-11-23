#include "stdafx.h"
#include "..\Headers\Player.h"

Player::Player(_lpd3dd9 pDevice)
	: GameObject(pDevice)
	, m_vAngle(0.f,0.f,0.f)
{
}

HRESULT Player::ReadyGameObjectPrototype()
{
	if (FAILED(GameObject::ReadyGameObjectPrototype()))
		return E_FAIL;

	m_vPos = _vector3(0.f, 0.f, 0.f);

	Vertex vertices[8];
	vertices[0] = Vertex(-1.f, -1.f, -1.f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[1] = Vertex(-1.f, 1.f, -1.f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[2] = Vertex(1.f, 1.f, -1.f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[3] = Vertex(1.f, -1.f, -1.f,D3DCOLOR_XRGB(255, 0, 0));
	vertices[4] = Vertex(-1.f, -1.f, 1.f,D3DCOLOR_XRGB(255, 0, 0));
	vertices[5] = Vertex(-1.f, 1.f, 1.f,D3DCOLOR_XRGB(255, 0, 0));
	vertices[6] = Vertex(1.f, 1.f, 1.f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[7] = Vertex(1.f, -1.f, 1.f, D3DCOLOR_XRGB(255, 0, 0));

	WORD indices[36];

	// ����
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	//�ĸ�
	indices[6] = 4;
	indices[7] = 6;
	indices[8] = 5;
	indices[9] = 4;
	indices[10] = 7;
	indices[11] = 6;

	//���� ����
	indices[12] = 4;
	indices[13] = 5;
	indices[14] = 1;
	indices[15] = 4;
	indices[16] = 1;
	indices[17] = 0;

	//������ ����
	indices[18] = 3;
	indices[19] = 2;
	indices[20] = 6;
	indices[21] = 3;
	indices[22] = 6;
	indices[23] = 7;

	//���
	indices[24] = 1;
	indices[25] = 5;
	indices[26] = 6;
	indices[27] = 1;
	indices[28] = 6;
	indices[29] = 2;

	//�ϴ�
	indices[30] = 4;
	indices[31] = 0;
	indices[32] = 3;
	indices[33] = 4;
	indices[34] = 3;
	indices[35] = 7;

	m_pVertices = VIBuffer::Create(m_pDevice, vertices, 8, indices, 36, 1);
	//assert(m_pVertices);
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

HRESULT Player::AddComponent()
{
	return E_NOTIMPL;
}

Player* Player::Create(_lpd3dd9 pDevice)
{
	if (nullptr == pDevice) { return nullptr; }
	Player* pInstance = new Player(pDevice);
	if (FAILED(pInstance->ReadyGameObjectPrototype()))
	{
		LOG_MSG(L"Error", L"Player Create has Failed");
		SafeRelease(pInstance);

		return nullptr;
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
}

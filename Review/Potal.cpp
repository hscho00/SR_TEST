#include "stdafx.h"
#include "Potal.h"
#include "GameObject_Manager.h"
#include "Texture_Manager.h"
#include "Client_Manager.h"
#include "Scroll_Manager.h"
#include "Graphic_Device.h"
#include "Terrain.h"

Portal::Portal()
{
}


Portal::~Portal()
{
}

Portal * Portal::Create(const _vec3 & _pos, wstring _connected_stage_name)
{
	Portal* pInstance = new Portal;
	pInstance->Ready_Potal(_pos, _connected_stage_name);
	if (FAILED(pInstance->Ready_Game_Object()))
	{
		delete pInstance;
		pInstance = nullptr;
	}

	return pInstance;
}

void Portal::Ready_Potal(const _vec3 & _pos, wstring _connected_stage_name)
{
	m_tInfo.vPos = _pos;
	Connected_stage_name_ = _connected_stage_name;
}

void Portal::RenderTexture()
{
	const TEXINFO* pTexInfo = Texture_Manager::Get_Instance()->Get_TexInfo
	(
		obj_key_,
		state_key_,
		L"",
		(DWORD)m_tFrame.fStartFrame
	);

	if (nullptr == pTexInfo) { return; }

	float fCenterX = _Float(pTexInfo->tImageInfo.Width >> 1);
	float fCenterY = _Float(pTexInfo->tImageInfo.Height >> 1);

	_matrix	matScale, matRotZ, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, m_tInfo.vSize.x* 0.8f, m_tInfo.vSize.y * 0.8f, 0.f);


	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x + Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_X), m_tInfo.vPos.y + Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_Y), 0.f); // À§Ä¡
	matWorld = matScale * matTrans;
	GraphicDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);
	GraphicDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Portal::RenderCollisionbox()
{
	GraphicDevice::Get_Instance()->Get_Sprite()->End();

	INT	Temp_Frame = 0;

	_vec2 Collision_Point[5] =
	{
		{ float(m_CurrentCollisionBox.left), float(m_CurrentCollisionBox.top) },
		{ float(m_CurrentCollisionBox.right), float(m_CurrentCollisionBox.top) },
		{ float(m_CurrentCollisionBox.right), float(m_CurrentCollisionBox.bottom) },
		{ float(m_CurrentCollisionBox.left), float(m_CurrentCollisionBox.bottom) },
		{ float(m_CurrentCollisionBox.left), float(m_CurrentCollisionBox.top) }
	};

	for (auto& _vec3 : Collision_Point)
	{
		_vec3.x += Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_X);
		_vec3.y += Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_Y);
	}

	GraphicDevice::Get_Instance()->Get_Line()->SetWidth(2.f);
	GraphicDevice::Get_Instance()->Get_Line()->Draw(Collision_Point, 5, D3DCOLOR_ARGB(255, 0, 0, 255));
	GraphicDevice::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

HRESULT Portal::Ready_Game_Object()
{
	obj_key_ = L"Object";
	state_key_ = L"Portal";
	m_tInfo.vSize = _vec3(1.f, 1.f, 0.f);
	m_tInfo.fFrameSpeed = 1.f;

	m_tFrame =
	{
		0.f,
		float(Texture_Manager::Get_Instance()->Get_TexPath(L"Object",L"Portal", L"")->dwCount)
	};

	CollisionBox.emplace_back(_vec2(40.f, 40.f));

	return S_OK;
}

_Int Portal::Update_Game_Object()
{
	if (m_bDead)
	{
		Terrain::Get_Instance()->Set_StageInfo(Connected_stage_name_.c_str(), TRUE);
		return OBJ_DEAD;
	}

	CollisionBox_Update();

	return OBJ_NOEVENT;
}

void Portal::LateUpdate_Game_Object()
{
	Frame_Update(m_tInfo.fFrameSpeed);
}

void Portal::Render_Game_Object()
{
	RenderTexture();

	if (ClientManager::Get_Instance()->Get_showsEdit(ClientManager::COllISIONBOX))
	{
		RenderCollisionbox();
	}
}

void Portal::Release_Game_Object()
{
}

void Portal::CollisionBox_Update()
{
	INT	Temp_Frame = 0;

	m_CurrentCollisionBox =
	{
		long(m_tInfo.vPos.x - CollisionBox[Temp_Frame].x),
		long(m_tInfo.vPos.y - CollisionBox[Temp_Frame].y),
		long(m_tInfo.vPos.x + CollisionBox[Temp_Frame].x),
		long(m_tInfo.vPos.y + CollisionBox[Temp_Frame].y),
	};
}

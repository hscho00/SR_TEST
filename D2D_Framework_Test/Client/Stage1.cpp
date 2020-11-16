#include "stdafx.h"
#include "Stage1.h"
#include "Texture_Manager.h"
#include "ObjManager.h"
#include "Graphic_Device.h"
#include "ScrollManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

#include "Player.h"
#include "Terrain.h"


CStage1::CStage1()
	: m_pPlayer(nullptr)
{

}

CStage1::~CStage1()
{
	Release_Scene();
}

HRESULT CStage1::Ready_Scene()
{
	//
	if (FAILED(CTexture_Manager::Get_Instance()->LoadMultiTextureFromPath(L"../Data/PathInfo.txt")))
	{
		ERR_MSG(L"Tile Image Insert Failed");
		return E_FAIL;
	}

	// ObjMgr : vector reserve
	m_pObjMgr->Init_ObjMgr(SCENE::ID::STAGE_1);

	/*-----Field------*/
	// Terrain
	Init_Field_0();

	m_eCurField = FIELD_0;
	/*----------------*/

	// Player
	m_pPlayer = static_cast<CPlayer*>(m_pObjMgr->Get_ObjOrNull(OBJ::ID::PLAYER, 0));
	if (!m_pPlayer)
	{
		m_pPlayer = new CPlayer;
		m_pPlayer->Init();
		m_pObjMgr->Add_Object(m_pPlayer, OBJ::ID::PLAYER);
	}

	return S_OK;
}

void CStage1::Update_Scene()
{
	ChangeField();
	m_pObjMgr->Update_ObjMgr();
}

void CStage1::LateUpdate_Scene()
{
	m_pObjMgr->LateUpdate_ObjMgr();
}

void CStage1::Render_Scene()
{
	m_pObjMgr->Render_ObjMgr();
}

void CStage1::Release_Scene()
{
	for (int i = 0; i < FIELD_END; ++i)
		m_vecObjInField[i].clear();

	m_pObjMgr->Delete_Objects(OBJ::ID::TERRAIN);
}

void CStage1::ChangeField()
{
	if (m_ePreField != m_eCurField)
	{
		Set_UsingAllInField(m_ePreField, false, m_bIsInit);

		switch (m_eCurField)
		{
		case FIELD_0:
			Set_Field_0();
			break;
		//case S1_END:
		//	g_SceneMgr->ChangeScene(CSceneMgr::SCENE_ENDING);
			break;
		}

		m_ePreField = m_eCurField;
		m_bIsInit = true;
	}
}

void CStage1::Init_Field_0()
{
	/*--------------------------------------*/
	FIELD_ID fieldID = FIELD_0;
	DWORD terrainID = 0;	// Hero Home 2F
	/*--------------------------------------*/

	CTerrain* pTerrain = new CTerrain(terrainID);
	pTerrain->Init();
	m_pObjMgr->Add_Object(pTerrain, OBJ::ID::TERRAIN);
	m_vecObjInField[fieldID].push_back(pTerrain);

	Set_UsingAllInField(fieldID, false, true);
}

void CStage1::Set_Field_0()
{
	/*--------------------------------------*/
	DWORD terrainID = 0;	// Hero Home 2F
	/*--------------------------------------*/

	Set_UsingAllInField(m_eCurField, true, m_bIsInit);

	if (!m_bIsInit)
		return;

	//
	CTerrain* pTerrain = static_cast<CTerrain*>(m_pObjMgr->Get_ObjOrNull(OBJ::ID::TERRAIN, terrainID));
	assert(pTerrain);

	m_pPlayer->Init_Terrain(pTerrain);
	
	if (m_ePreField == FIELD_END)
	{
		m_pPlayer->Set_CurTile_Force(71);
	}
	else
	{
		m_pPlayer->Set_CurTile_Force(30);
		m_pPlayer->Set_NextTileIdx(31, OBJ::DIR::RIGHT);
	}

	DWORD terrainWidth = pTerrain->Get_TileCntX() * TILECX;
	DWORD terrainHeight = pTerrain->Get_TileCntY() * TILECY;
	CScrollManager::Init_Scroll(terrainWidth, terrainHeight);
}
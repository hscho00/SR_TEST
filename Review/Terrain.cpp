#include "stdafx.h"
#include "Terrain.h"
#include "Graphic_Device.h"
#include "Texture_Manager.h"
#include "Time_Manager.h"
#include "Scroll_Manager.h"
#include "Player.h"
#include "GameObject_Manager.h"
#include "Potal.h"
#include "MonsterSponer.h"
#include "SoundMgr.h"

IMPLEMENT_SINGLETON(Terrain)

Terrain::Terrain()
	: m_StageInfo(nullptr), m_ViewTile(FALSE)
{
}

Terrain::~Terrain()
{
	Release_Terrain();
}

void Terrain::TileChange_Terrain(const _vec3 & vPos, const BYTE & byDrawID, const BYTE & byOption)
{
	if (!m_StageInfo)
	{
		return;
	}
	int iIndex = Get_TileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_StageInfo->StageTile[iIndex]->byDrawID = byDrawID;
	m_StageInfo->StageTile[iIndex]->byOption = byOption;
}

HRESULT Terrain::Load_StageData()
{
	CString strFilePath = L"../Data/Client/Stage/Terrain.dat";
	HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	DWORD dwStrByte = 0;
	DWORD dwByte = 0;
	DWORD dwByte2 = 0;
	int		TileCount = 0;
	STAGEINFO* pStageInfo = nullptr;
	while (true)
	{
		pStageInfo = new STAGEINFO;

		// 스테이지 타이틀 글자 수 로드 및 타이틀 로드
		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);	// 스테이지 네임 글자 수
		TCHAR* pszBuf = new TCHAR[dwStrByte];
		ReadFile(hFile, pszBuf, dwStrByte, &dwByte, nullptr);	// 스테이지 네임
		pStageInfo->StageName = pszBuf;
		delete[] pszBuf;

		// 스테이지의 오브젝트 키의 글자 수 및 타이틀 로드
		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);	// 스테이지 네임 글자 수
		TCHAR* pszBuf2 = new TCHAR[dwStrByte];
		ReadFile(hFile, pszBuf2, dwStrByte, &dwByte, nullptr);	// 스테이지 네임
		pStageInfo->ObjectKey = pszBuf2;
		delete[] pszBuf2;

		// 높이, 너비, 타일의 가로 개수, 타일의 세로 개수

		ReadFile(hFile, &(pStageInfo->Height), sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &pStageInfo->Width, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &pStageInfo->StageTileWidth, sizeof(int), &dwByte, nullptr);
		ReadFile(hFile, &pStageInfo->StageTileHeight, sizeof(int), &dwByte, nullptr);

		// 타일 벡터의 개수와 타일 벡터 로드

		ReadFile(hFile, &TileCount, sizeof(int), &dwByte, nullptr);

		TILE* pTile = nullptr;

		for (int i = 0; i < TileCount; i++)
		{
			pTile = new TILE;
			ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);
			if (0 == dwByte)
			{
				Safe_Delete(pTile);
				break;
			}
			pStageInfo->StageTile.emplace_back(pTile);
		}

		if (0 == dwByte)
		{
			Safe_Delete(pStageInfo);
			break;
		}

		m_mapStage.emplace(pStageInfo->StageName, pStageInfo);

	}
	CloseHandle(hFile);

	// 툴로 작업하지 않고 하드 코딩 하는 영역
	POTALINFO* pPotalInfo = new POTALINFO;
	pPotalInfo->potal_info = _vec3(550.f, 1150.f, 0.f);
	pPotalInfo->player_pos = _vec3(650.f, 1050.f, 0.f);
	m_mapStage["Town"]->Potal_Info.emplace(L"Field", pPotalInfo);
	POTALINFO* pPotalInfo2 = new POTALINFO;
	pPotalInfo2->potal_info = _vec3(1664.f, 919.f, 0.f);
	pPotalInfo2->player_pos = _vec3(1664.f, 1019.f, 0.f);
	m_mapStage["Field"]->Potal_Info.emplace(L"Town", pPotalInfo2);

	int BlueWolf_index[5] = {992, 1235, 1236, 1238, 1240};

	for (int i : BlueWolf_index)
	{
		SponerInfo* pSponerInfo = new SponerInfo;
		pSponerInfo->tile_index = i;
		pSponerInfo->spon_monster_name = L"BlueWolf";
		m_mapStage["Field"]->stage_sponer.emplace_back(pSponerInfo);
	}

	int bluewolfwizard_index[1] = { 1253 /*,1251, 1247, 1245*/ };

	for (int i : bluewolfwizard_index)
	{
		SponerInfo* pSponerInfo3 = new SponerInfo;
		pSponerInfo3->tile_index = i;
		pSponerInfo3->spon_monster_name = L"BlueWolfWizard";
		m_mapStage["Field"]->stage_sponer.emplace_back(pSponerInfo3);
	}

	Create_Graph_Terrain();
	return S_OK;
}

int Terrain::Get_TileIndex(const _vec3 & vPos)
{
	if (!m_StageInfo) { return -1; }
	
	for (size_t i = 0; i < m_StageInfo->StageTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}
	return -1;
}

bool Terrain::IsPicking(const _vec3 & vPos, const int & iIndex)
{
	_vec3 vPoint[4] =
	{
		{ m_StageInfo->StageTile[iIndex]->vPos.x, m_StageInfo->StageTile[iIndex]->vPos.y + (TILECY * 0.5f), 0.f },
		{ m_StageInfo->StageTile[iIndex]->vPos.x + (TILECX * 0.5f), m_StageInfo->StageTile[iIndex]->vPos.y , 0.f },
		{ m_StageInfo->StageTile[iIndex]->vPos.x, m_StageInfo->StageTile[iIndex]->vPos.y - (TILECY * 0.5f), 0.f },
		{ m_StageInfo->StageTile[iIndex]->vPos.x - (TILECX * 0.5f), m_StageInfo->StageTile[iIndex]->vPos.y , 0.f }
	};


	_vec3 vRhombusDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3]
	};

	//3
	_vec3 vRhombusNormal[4] =
	{
		{ -vRhombusDir[0].y, vRhombusDir[0].x, 0.f },
		{ -vRhombusDir[1].y, vRhombusDir[1].x, 0.f },
		{ -vRhombusDir[2].y, vRhombusDir[2].x, 0.f },
		{ -vRhombusDir[3].y, vRhombusDir[3].x, 0.f }
	};

	//4 
	_vec3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3],

	};
 
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3Normalize(&vMouseDir[i], &vMouseDir[i]);
		D3DXVec3Normalize(&vRhombusNormal[i], &vRhombusNormal[i]);

		if (0 < D3DXVec3Dot(&vRhombusNormal[i], &vMouseDir[i]))
			return false;
	}
	return true;
}

void Terrain::Background_Render()
{
	if (!m_StageInfo)
	{
		return;
	}
	_matrix matScale, matTrans, matWrold;
	const TEXINFO* pTexInfo = Texture_Manager::Get_Instance()->Get_TexInfo((wstring)m_StageInfo->ObjectKey);
	assert(!(nullptr == pTexInfo));

	float fCenterX = float(WINCX >> 1);	// 이미지의 중점
	float fCenterY = float(WINCY >> 1);	// 이미지의 중점
	
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);	// 크기
	D3DXMatrixTranslation(&matTrans, WINCX/2 + Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_X), WINCY/2 + Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_Y), 0.f);
	matWrold = matScale * matTrans;

	GraphicDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
	GraphicDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void Terrain::Tile_Render()
{
	_matrix matScale, matTrans, matWrold;

	TCHAR szBuf[MAX_PATH] = L"";
	int iIndex = 0;
	DWORD dwSize = m_StageInfo->StageTile.size();
	for (size_t i = 0; i < dwSize; ++i)
	{
		swprintf_s(szBuf, __T("%d"), iIndex);
		const TEXINFO* pTexInfo = Texture_Manager::Get_Instance()->Get_TexInfo(L"Tile", L"", L"", m_StageInfo->StageTile[i]->byDrawID);
		//assert(!(nullptr == pTexInfo));

		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
		SB_HORZ; SB_VERT;
		D3DXMatrixScaling(&matScale, m_StageInfo->StageTile[i]->vSize.x, m_StageInfo->StageTile[i]->vSize.y, 0.f);
		D3DXMatrixTranslation(&matTrans, m_StageInfo->StageTile[i]->vPos.x + Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_X), m_StageInfo->StageTile[i]->vPos.y + Scroll_Manager::Get_Scroll(Scroll_Manager::SCROLL_Y), 0.f);
		matWrold = matScale * matTrans;

		GraphicDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWrold);
		GraphicDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

		/*Graphic_Device::Get_Instance()->Get_Font()->DrawTextW(Graphic_Device::Get_Instance()->Get_Sprite(), szBuf, lstrlen(szBuf), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));*/
		++iIndex;
	}
}

void Terrain::Mini_Render_Terrain()
{
	//_matrix matScale, matTrans, matWorld, matRatio;

	//DWORD Size = m_vecTile.size();	// 타일 개수

	//for (size_t i = 0; i < Size; ++i)
	//{
	//	const TEXINFO* pTexInfo = Texture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Tile", L"",m_vecTile[i]->byDrawID);
	//	assert(!(nullptr == pTexInfo));

	//	float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
	//	float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
	//}
}

void Terrain::Create_Graph_Terrain()
{
	for(auto& pStage : m_mapStage)
	{
		pStage.second->graph_tile.resize(pStage.second->StageTile.size());

		for (int i = 0; i < pStage.second->StageTileHeight; ++i)
		{
			for (int j = 0; j < pStage.second->StageTileWidth; ++j)
			{
				int iIndex = j + (pStage.second->StageTileWidth * i);

				// 좌측 상단 0
				if (0 != i && 0 != iIndex % (pStage.second->StageTileWidth * 2))
				{
					if (0 == i % 2 && 0 == pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth + 1)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth + 1)]);
					else if (0 != i % 2 && 0 == pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth)]);
				}

				// 우측 상단 1
				if (0 != i && (pStage.second->StageTileWidth * 2) - 1 != iIndex % (pStage.second->StageTileWidth * 2))
				{
					if (0 == i % 2 && 0 == pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth)]);
					else if (0 != i % 2 && 0 == pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth - 1)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex - (pStage.second->StageTileWidth - 1)]);
				}

				// 좌측 하단 2
				if (pStage.second->StageTileHeight - 1 != i && 0 != iIndex % (pStage.second->StageTileWidth * 2))
				{
					if (0 == i % 2 && 0 == pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth - 1)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth - 1)]);
					else if (0 != i % 2 && 0 == pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth)]);
				}

				// 우측 하단 3
				if (pStage.second->StageTileHeight - 1 != i && (pStage.second->StageTileWidth * 2) - 1 != iIndex % (pStage.second->StageTileWidth * 2))
				{
					if (0 == i % 2 && 0 == pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth)]);
					else if (0 != i % 2 && 0 == pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth + 1)]->byOption)
						pStage.second->graph_tile[iIndex].emplace_back(pStage.second->StageTile[iIndex + (pStage.second->StageTileWidth + 1)]);
				}
			}
		}
	}
}

Terrain * Terrain::Create()
{
	Terrain* pInstance = new Terrain;
	if (FAILED(pInstance->Ready_Terrain()))
	{
		Safe_Delete(pInstance);
		return nullptr;
	}
	return pInstance;
}

HRESULT Terrain::Ready_Terrain()
{
	if (m_StageInfo == nullptr)
	{
		return S_OK;
	}
	
	//TILE* pTile = nullptr;
	//m_StageInfo->StageTile.reserve(m_StageInfo->StageTileWidth * m_StageInfo->StageTileHeight);
	//float fX = 0.f;
	//float fY = 0.f;
	//for (int i = 0; i < m_StageInfo->StageTileHeight; ++i)
	//{
	//	for (int j = 0; j < m_StageInfo->StageTileWidth; ++j)
	//	{
	//		pTile = new TILE;
	//		fX = float((j * TILECX) + (i % 2) * (TILECX >> 1));
	//		fY = float((TILECY >> 1) * i);
	//		pTile->vPos = { fX, fY, 0.f };
	//		pTile->vSize = { 1.f, 1.f, 0.f };
	//		pTile->byDrawID = 0;
	//		pTile->byOption = 0;
	//		m_StageInfo->StageTile.emplace_back(pTile);
	//	}
	//}
	return S_OK;
}

int Terrain::Update_Terrain()
{
	float fTimeDelta = Time_Manager::Get_Instance()->Get_TimeDelta();
	float fSpeed = 300.f * fTimeDelta;
	return 0;
}

void Terrain::Late_Update_Terrain()
{
}

void Terrain::Render_Terrain()
{
	if (!m_StageInfo)
	{
		return;
	}

	Background_Render();

	if (m_ViewTile)
	{
		Tile_Render();
	}

}

void Terrain::Release_Terrain()
{
	for (auto& pInfo : m_mapStage)
	{
		for (auto& pTile : pInfo.second->StageTile)
		{
			Safe_Delete(pTile);
		}
		pInfo.second->StageTile.clear();
		pInfo.second->StageTile.shrink_to_fit();
		for (auto pPotal : pInfo.second->Potal_Info)
		{
			Safe_Delete(pPotal.second);
		}
		pInfo.second->Potal_Info.clear();

		for (auto pSponerInfo : pInfo.second->stage_sponer)
		{
			Safe_Delete(pSponerInfo);
		}
		pInfo.second->stage_sponer.clear();
		pInfo.second->stage_sponer.shrink_to_fit();

		Safe_Delete(pInfo.second);
	}
	m_mapStage.clear();
}

void Terrain::Set_StageInfo(StageInfo* _pStage)
{
	m_StageInfo = _pStage;
	Scroll_Manager::Set_TerrainSize(_vec3{(float)m_StageInfo->Width, (float)m_StageInfo->Height, 0.f });
}

void Terrain::Set_StageInfo(CString _StageTitle, BOOL _StartPos /*= FALSE*/)
{
	wstring pPreStageTitle;
	if (_StartPos)
	{
		pPreStageTitle = m_StageInfo->StageName;
	}
	m_StageInfo = m_mapStage[_StageTitle];
	for (auto& potal_info : m_StageInfo->Potal_Info)
	{
		GameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_POTAL, Portal::Create(potal_info.second->potal_info, potal_info.first));
	}



	// 플레이어 좌표 값 및 스크롤 값 수정
	Scroll_Manager::Set_TerrainSize(_vec3{ (float)m_StageInfo->Width,(float)m_StageInfo->Height, 0.f });
	if (_StartPos)
	{
		auto& iter_find = m_StageInfo->Potal_Info.find(pPreStageTitle);
		if (iter_find == m_StageInfo->Potal_Info.end())
		{
	/*		GameObject_Manager::Get_Instance()->Get_Player()->Set_Pos(_vec3(WINCX/2 * 1.f, WINCY/2 * 1.f, 0.f));*/
		}
		else
		{
			GameObject_Manager::Get_Instance()->Get_Player()->Set_Pos(iter_find->second->player_pos);
			_Float ScrollX = WINCX / 2 - iter_find->second->player_pos.x;
			_Float ScrollY = WINCY / 2 - iter_find->second->player_pos.y;
			static_cast<Player*>(GameObject_Manager::Get_Instance()->Get_Player())->Off_Set();
			static_cast<Player*>(GameObject_Manager::Get_Instance()->Get_Player())->Stop();
		}
	}

	// 지워야 할 오브젝트 삭제
	GameObject_Manager::Get_Instance()->Delete_ID(OBJID::OBJ_MONSTER);
	GameObject_Manager::Get_Instance()->Delete_ID(OBJID::OBJ_ETC);

	for (auto& sponer_info : m_StageInfo->stage_sponer)
	{
		GameObject_Manager::Get_Instance()->Add_GameObject_Manager(OBJID::OBJ_ETC, MonsterSponer::Create(sponer_info->spon_monster_name, sponer_info->tile_index));
	}
	
	CString temp = m_StageInfo->StageName + L".wav";
	
	TCHAR SoundTitle[MAX_PATH];
	lstrcpy(SoundTitle, temp.GetString());
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::STAGE);
	CSoundMgr::Get_Instance()->PlaySound(SoundTitle, CSoundMgr::STAGE);

}

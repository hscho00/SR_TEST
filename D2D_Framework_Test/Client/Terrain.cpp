#include "stdafx.h"
#include "Terrain.h"
#include "Graphic_Device.h"
#include "Texture_Manager.h"
#include "ScrollManager.h"

#include "TimeManager.h"
#include "KeyManager.h"


CTerrain::CTerrain(DWORD id)
	: m_pBgTexInfo(nullptr)
	, m_dwID(id)
	, m_dwTileCntX(0)
	, m_dwTileCntY(0)
{
	m_ObjID = OBJ::ID::TERRAIN;
	m_RenderGroup = OBJ::RENDER_GROUP::BACKGROUND;

	//
	WCHAR szFilePath[MAX_PATH] = L"../Data/Terrain_%d.dat";
	swprintf_s(szFilePath, szFilePath, m_dwID);

	if (FAILED(LoadTerrain(szFilePath)))
	{
		ERR_MSG(L"Load Terrain Failed");
		//return E_FAIL;
	}
}

CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::Init()
{
	return S_OK;
}

OBJ::EVENT CTerrain::Update()
{
	return OBJ::EVENT::NO_EVENT;
}

void CTerrain::LateUpdate()
{

}

void CTerrain::Render()
{
	assert(m_pBgTexInfo);

	LPD3DXSPRITE pSprite = CGraphic_Device::Get_Instance()->Get_Sprite();
	D3DCOLOR whiteColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	float fScrollX = CScrollManager::Get_Scroll(CScrollManager::SCROLL_X);
	float fScrollY = CScrollManager::Get_Scroll(CScrollManager::SCROLL_Y);

#ifdef _DEBUG
	LPD3DXFONT pFont = CGraphic_Device::Get_Instance()->Get_Font();
	LPD3DXLINE pLine = CGraphic_Device::Get_Instance()->Get_Line();
	list<TILE*> listOptionTile;
	TCHAR szBuf[MAX_PATH] = _T("");
	D3DCOLOR optionColor = D3DCOLOR_ARGB(255, 255, 255, 255);
#endif

	_matrix matScale, matTrans, matParentScale, matParentTrans, matWorld;
	D3DXMatrixScaling(&matScale, 3.f, 3.f, 0.f);
	D3DXMatrixTranslation(&matTrans, -fScrollX, -fScrollY, 0.f);
	matWorld = matScale * matTrans;
	pSprite->SetTransform(&matWorld);

	// Draw BG
	pSprite->Draw(m_pBgTexInfo->pTexture, nullptr, &_vec3(0.f, 0.f, 0.f), nullptr, whiteColor);

	//
	for (auto& it = m_vecTile.begin(); it != m_vecTile.end(); ++it)
	{
		TILE* pTile = *it;
#ifdef _DEBUG
		if (g_bDebugMode)
		{
			// Draw Font
			if (pTile->byOption != 0)
			{
				listOptionTile.push_back(pTile);

				switch (pTile->byOption)
				{
				case 2:	// Map Change
					optionColor = D3DCOLOR_ARGB(255, 0, 0, 255);
					break;
				case 3:	// Map Change(Door)
					optionColor = D3DCOLOR_ARGB(255, 0, 255, 255);
					break;
				case 6:	// EventTrigger
					optionColor = D3DCOLOR_ARGB(255, 0, 0, 0);
					break;
				default:
					optionColor = whiteColor;
					break;
				}

				if (optionColor != whiteColor)
				{
					_stprintf_s(szBuf, _T("%d"), pTile->dwExtra);
					D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
					D3DXMatrixTranslation(&matTrans, pTile->vPos.x + (TILECX * 0.6f) - fScrollX, pTile->vPos.y + (TILECY * 0.5f) - fScrollY, 0.f);
					matWorld = matScale * matTrans;
					pSprite->SetTransform(&matWorld);
					pFont->DrawText(pSprite, szBuf, _tcslen(szBuf), nullptr, 0, optionColor);
				}

				//
				_stprintf_s(szBuf, _T("%d"), pTile->dwIndex);
				D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
				D3DXMatrixTranslation(&matTrans, pTile->vPos.x - fScrollX, pTile->vPos.y - fScrollY, 0.f);
				matWorld = matScale * matTrans;
				pSprite->SetTransform(&matWorld);
				pFont->DrawText(pSprite, szBuf, _tcslen(szBuf), nullptr, 0, whiteColor);
			}
		}
#endif
		// Draw Open Door, Grass etc...
		if (!pTile->bDraw)
			continue;

		const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", pTile->wstrStateKey, 0);
		assert(!(nullptr == pTexInfo));

		D3DXMatrixScaling(&matScale, 1.f, 1.f, 0.f);
		D3DXMatrixTranslation(&matTrans, pTile->vPos.x + (TILECX >> 1) - fScrollX, pTile->vPos.y + (TILECY >> 1) - fScrollY, 0.f);
		matWorld = matScale * matTrans;
		pSprite->SetTransform(&matWorld);

		float fCenterX = float(pTexInfo->tImageInfo.Width >> 1);
		float fCenterY = float(pTexInfo->tImageInfo.Height >> 1);
		pSprite->Draw(pTexInfo->pTexture, nullptr, &_vec3(fCenterX, fCenterY, 0.f), nullptr, whiteColor);
	}

#ifdef _DEBUG
	if (g_bDebugMode)
	{
		// Draw Line
		pSprite->End();

		pLine->SetWidth(4.f);
		for (TILE* pOptionTile : listOptionTile)
		{
			float offset = 2.f;
			D3DXVECTOR2 vLinePos[5] = { {pOptionTile->vPos.x + offset, pOptionTile->vPos.y + offset},
										{pOptionTile->vPos.x + (float)TILECX - offset, pOptionTile->vPos.y + offset},
										{pOptionTile->vPos.x + (float)TILECX - offset, pOptionTile->vPos.y + (float)TILECY - offset},
										{pOptionTile->vPos.x + offset, pOptionTile->vPos.y + (float)TILECY - offset},
										{pOptionTile->vPos.x + offset, pOptionTile->vPos.y + offset} };

			for (int i = 0; i < 5; ++i)
			{
				vLinePos[i].x -= fScrollX;
				vLinePos[i].y -= fScrollY;
			}

			switch (pOptionTile->byOption)
			{
			case 1:	// No Enter
				optionColor = D3DCOLOR_ARGB(255, 255, 0, 0);
				break;
			case 2:	// Map Change
				optionColor = D3DCOLOR_ARGB(255, 0, 0, 255);
				break;
			case 3:	// Map Change(Door)
				optionColor = D3DCOLOR_ARGB(255, 0, 255, 255);
				break;
			case 4:	// Grass
				optionColor = D3DCOLOR_ARGB(255, 0, 255, 0);
				break;
			case 5:	// Hill
				optionColor = D3DCOLOR_ARGB(255, 150, 75, 0);
				break;
			case 6:	// EventTrigger
				optionColor = D3DCOLOR_ARGB(255, 0, 0, 0);
				break;
			default:
				optionColor = whiteColor;
				break;
			}

			pLine->Draw(vLinePos, 5, optionColor);
		}
		listOptionTile.clear();

		pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	}
#endif
}

void CTerrain::Release()
{
	for (auto& pTile : m_vecTile)
		Safe_Delete(pTile);
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTerrain::Set_Using(bool bUsing)
{
	m_bUsing = bUsing;
	m_bDraw = bUsing;

	for (auto& pTile : m_vecTile)
		pTile->bDraw = false;
}

HRESULT CTerrain::Get_TileCenterPos(_vec3* pOut, const DWORD dwIndex) const
{
	if (dwIndex < 0 || dwIndex > m_vecTile.size())
		return E_FAIL;

	*pOut = (m_vecTile[dwIndex]->vPos + _vec3((float)TILECX * 0.5f, (float)TILECY * 0.5f, 0.f));

	return S_OK;
}

HRESULT CTerrain::LoadTerrain(const wstring& wstrFilePath)
{
	//
	HANDLE hFile = CreateFile(wstrFilePath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE)
		return E_FAIL;

	//
	DWORD dwReadBytes = 0;
	DWORD dwStrBytes = 0;

	//
	Release();

	// ID, TileCX, TileCY
	DWORD id = (DWORD)-1;
	ReadFile(hFile, &id, sizeof(DWORD), &dwReadBytes, nullptr);
	assert(id == m_dwID);
	ReadFile(hFile, &m_dwTileCntX, sizeof(DWORD), &dwReadBytes, nullptr);
	ReadFile(hFile, &m_dwTileCntY, sizeof(DWORD), &dwReadBytes, nullptr);
	
	//
	m_pBgTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Terrain", L"Background", id);
	assert(!(nullptr == m_pBgTexInfo));

	// Tile
	m_vecTile.reserve(m_dwTileCntX * m_dwTileCntY);
	TILE tile = {};

	while (true)
	{
		unsigned int size = sizeof(TILE) - sizeof(wstring);	// wstrStateKey;
		ReadFile(hFile, &tile, size, &dwReadBytes, nullptr);
		if (dwReadBytes == 0)
			break;

		ReadFile(hFile, &dwStrBytes, sizeof(DWORD), &dwReadBytes, nullptr);
		WCHAR szStateKey[MAX_PATH] = L"";
		ReadFile(hFile, szStateKey, dwStrBytes, &dwReadBytes, nullptr);
		tile.wstrStateKey = szStateKey;

		m_vecTile.push_back(new TILE(tile));
	}

	// Terrain Load End
	CloseHandle(hFile);

	return S_OK;
}

#pragma once
#include "Obj.h"

class CTerrain final : public CObj
{
public:
	explicit CTerrain(DWORD id);
	virtual ~CTerrain();

public:
	virtual HRESULT Init() override;
	virtual OBJ::EVENT Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;

private:
	virtual void Release() override;

public:
	virtual void Set_Using(bool bUsing);

public:
	const vector<TILE*>& Get_VecTile() { return m_vecTile; }

	DWORD Get_TileCntX() const { return m_dwTileCntX; }
	DWORD Get_TileCntY() const { return m_dwTileCntY; }

	HRESULT Get_TileCenterPos(_vec3* pOut, const DWORD dwIndex) const;

private:
	HRESULT LoadTerrain(const wstring& wstrFilePath);

private:
	// 배경
	const TEXINFO* m_pBgTexInfo;

	// 타일
	vector<TILE*> m_vecTile;
	DWORD m_dwID;
	DWORD m_dwTileCntX;
	DWORD m_dwTileCntY;

};


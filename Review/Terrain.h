#pragma once

class Terrain
{
	DECLARE_SINGLETON(Terrain);

private:
	Terrain();

public:
	~Terrain();

public:
	void	TileChange_Terrain(const _vec3& vPos, const BYTE& byDrawID, const BYTE& byOption = 0);
	bool	IsPicking(const _vec3& vPos, const int& iIndex);
	void	Background_Render();
	HRESULT Load_StageData();
	void	Tile_Render();
	void	Mini_Render_Terrain();
	void	Create_Graph_Terrain();

public:
	static Terrain* Create();

public:
	HRESULT Ready_Terrain();
	int		Update_Terrain();
	void	Late_Update_Terrain();
	void	Render_Terrain();
	void	Release_Terrain();

public:
	void	Set_StageInfo(StageInfo* _pStage);
	void	Set_StageInfo(CString _StageTitle, BOOL _StartPos = FALSE);
	void	Set_ViewTile(BOOL _ViewTile) { m_ViewTile = _ViewTile; }

public:
	int		Get_TileIndex(const _vec3& vPos);
	BOOL	Get_ViewTile() { return m_ViewTile; }
	StageInfo* Get_StageInfo() { return  m_StageInfo; }

private:
	map<CString, StageInfo*> m_mapStage;
	StageInfo*		m_StageInfo;
	BOOL			m_ViewTile;
};


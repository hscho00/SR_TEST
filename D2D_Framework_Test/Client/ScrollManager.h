#pragma once

class CScrollManager
{
public:
	enum SCROLL_ID { SCROLL_X, SCROLL_Y };

public:
	CScrollManager() = default;
	~CScrollManager() = default;

public:
	static float Get_Scroll(SCROLL_ID eScrollID);
	static _vec3 Get_Scroll() { return m_vScroll; }
	static void Accumulate_Scroll(const _vec3& vAmount);
	static void Accumulate_ScrollX(float fAmount);
	static void Accumulate_ScrollY(float fAmount);

	static void ScrollRock();
	static void Init_Scroll(const DWORD terrainWidth, const DWORD terrainHeight );

private:
	static _vec3 m_vScroll;
	
	static DWORD m_dwTerrainWidth;
	static DWORD m_dwTerrainHeight;

	static BOOL m_bLockScrollX;
	static BOOL m_bLockScrollY;

};


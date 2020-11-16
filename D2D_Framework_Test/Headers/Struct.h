#pragma once

typedef struct tagTexturePath
{
	wstring wstrRelativePath;
	wstring wstrObjectKey;
	wstring wstrStateKey;
	DWORD	dwCount;
}TEXPATH;

typedef struct tagTexInfo
{
	LPDIRECT3DTEXTURE9	pTexture; 
	D3DXIMAGE_INFO		tImageInfo; 
}TEXINFO;

typedef struct tagTile
{
	tagTile()
		: dwIndex(0), vPos(_vec3(0.f, 0.f, 0.f)), byOption(0), dwExtra(0), bDraw(FALSE), wstrStateKey(L"")
	{}

	DWORD dwIndex;
	_vec3 vPos;				// Left-Top
	BYTE byOption;			// NoOption, NoEnter, MapChange, MapChange(Door), Grass, Hill, EventTrigger
	DWORD dwExtra;			// MapChange -> 다음 맵 id, EventTrigger-> 발생시킬 이벤트
	BOOL bDraw;				
	wstring wstrStateKey;	// Draw StateKey
}TILE;

typedef struct tagFrame
{
	BYTE byCurFrame;
	BYTE byEndFrame;
	float fCurFrameTime;
	float fResetFrameTime;
}FRAME;

typedef struct tagBackgroundObj
{
	OBJ::BGOBJ eID;
	_vec3 vPos;
	FRAME tFrame;
}BGOBJ;

typedef struct tagPokemonSkill
{
	BYTE byID;				// ID
	POKeMON::TYPE eType;	// 타입 (공격시 적용)
	BYTE byClass;			// 0 : 물리스킬, 1 : 변화스킬, 2 : 특수스킬(미사용)
	DWORD dwAtk;			// 위력
	DWORD dwHit;			// 명중
	DWORD dwPP;				// Power Point
	DWORD dwMaxPP;			// Max PP
	wstring skillName;		// 스킬 이름

}POKeSKILL;

typedef struct tagPokemonInfo
{
	enum { MAX_SKILL_CNT = 4 };
	enum { STAT_STR, STAT_DEF, STAT_HIT, STAT_END };

	///////////////////////////////////////////////////

	tagPokemonInfo()
		: byID(0)
		, rcBattleFront()
		, rcBattleRear()
		, rcInven()
		, bMale(true)
		, dwLevel(1)
		, dwExp(0)
		, dwMaxExp(999)
		, dwHP(999)
		, dwMaxHP(999)
		, dwStr(0)
		, dwDef(0)
		, eType(POKeMON::TYPE::NORMAL)
		, iStatRank()
		, tSkill()
		, pokeName(L"")
	{}

	///////////////////////////////////////////////////

	void Set_Rect(const LONG centerX, const LONG centerY)
	{
		rcBattleFront.left = centerX - 63;
		rcBattleFront.top = centerY - 63;
		rcBattleFront.right = centerX - 1;
		rcBattleFront.bottom = centerY - 1;

		rcBattleRear.left = centerX - 63;
		rcBattleRear.top = centerY + 2;
		rcBattleRear.right = centerX - 1;
		rcBattleRear.bottom = centerY + 64;

		rcInven[0].left = centerX - 35;
		rcInven[0].top = centerY - 88;
		rcInven[0].right = centerX - 1;
		rcInven[0].bottom = centerY - 66;

		rcInven[1].left = centerX + 1;
		rcInven[1].top = centerY - 88;
		rcInven[1].right = centerX + 35;
		rcInven[1].bottom = centerY - 66;
	}

	void Reset_Rank()
	{
		iStatRank[STAT_STR] = 0;
		iStatRank[STAT_DEF] = 0;
		iStatRank[STAT_HIT] = 0;
	}

	///////////////////////////////////////////////////

	BYTE byID;				// ID
	RECT rcBattleFront;		// Battle Front Rect. 3배 키워 그릴 것.
	RECT rcBattleRear;		// Battle Rear Rect. 3배 키워 그릴 것.
	RECT rcInven[2];		// 인벤토리에 띄울 렉트. 번갈아가면서 그림.
	BOOL bMale;				// true면 수컷 flase면 암컷
	DWORD dwLevel;			// Level
	DWORD dwExp;			// 현재 경험치
	DWORD dwMaxExp;			// 최대 경험치
	DWORD dwHP;				// Hp
	DWORD dwMaxHP;			// Max HP
	DWORD dwStr;			// 공격력
	DWORD dwDef;			// 방어력
	POKeMON::TYPE eType;	// 타입 (방어시 적용)
	int iStatRank[STAT_END];	// 변화 스킬에 의해 스탯 변함. 양수면 상승, 음수면 감소. 배틀 끝나면 0으로 초기화
	POKeSKILL tSkill[MAX_SKILL_CNT];	// 기술
	wstring pokeName;		// 포켓몬 이름

}POKeINFO;

typedef struct tagItem
{
	DWORD dwID;
	ITEM::CLASS eClass;
	wstring itemName;
	wstring itemDesc[3];
	DWORD dwIconID;
	DWORD dwCount;
}ITEMINFO;

////////////////////////////////////////////////////////////////////////////////

// 클라에서 안쓰임

typedef struct tagUnitInfo
{
#ifdef _AFX
	CString strName;
#else
	wstring strName;
#endif // _AFX
	
	int iAtk;
	int iDef;
	BYTE byJob;
	BYTE byItem;

}UNITINFO;

/*
typedef struct tagInfo
{
	D3DXVECTOR3 vPos; // 위치를 표현하기 위한 벡터. 
	D3DXVECTOR3 vDir; // 방향을 표현하기 위한 방향벡터.
	D3DXVECTOR3 vSize; // 
	D3DXVECTOR3 vLook; // 그냥 기준이 되는 축. 

}INFO;
*/
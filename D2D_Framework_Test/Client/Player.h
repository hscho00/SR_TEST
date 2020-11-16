#pragma once
#include "Obj.h"

class CTerrain;

class CPlayer final : public CObj
{
public:
    CPlayer();
    virtual ~CPlayer();

public:
    virtual HRESULT Init() override;
    virtual OBJ::EVENT Update() override;
    virtual void LateUpdate() override;
    virtual void Render() override;

private:
    virtual void Release() override;

public:
    void Init_Terrain(CObj* pTerrain);
    void Set_CurTile_Force(const DWORD idx);
    void Set_NextTileIdx(const DWORD idx, OBJ::DIR dir);

    //void Set_BattleEnd();   // BattleMgr Call this
    //void Set_FieldIDPreBattle(DWORD fieldID) { m_dwFieldIDPreBattle = fieldID; }  // Stage Call this

    //void Start_FadeOutIn();

    //POKeINFO* Get_PokeInfoOrNull(const DWORD idx);  // BattleMgr에서 받아서 값 수정
    //const vector<POKeINFO*>& Get_PokeVec() const { return m_vecPokemon; }   // UI에서 참고
    //void SwapPokemon(const DWORD idx);
    //void CatchPokemon(const POKeINFO& pokeInfo);

    //const DWORD Get_PokemonCount() const { return m_dwPokemonCnt; }
    //const DWORD Get_CurUICmd() const { return m_dwCurUICmd; }
    //const DWORD Get_CurUIDepth() const { return m_dwCurUIDepth; }
    //const DWORD Get_SelectUICmd() const { return m_dwSelectUICmd; }

    //const vector<ITEMINFO*>& Get_ItemsVec() const { return m_vecItems; }
    //const vector<ITEMINFO*>& Get_KeyItemsVec() const { return m_vecKeyItems; }
    //const vector<ITEMINFO*>& Get_PokeballsVec() const { return m_vecPokeBalls; }

private:
    void CheckKeyState();
    void CheckKeyState_Move();
    //void CheckKeyState_Menu();
    //void CheckKeyState_Dlg();

    void MovePlayer();
    void ScrollOffset();

    void CheckNextTile();
    
    //void CheckEventID(const DWORD eventID);
    //void Event_Stage1(const DWORD eventID);
    ////void Event_Stage2(const DWORD eventID);

    //void ShowMenu();

    //void BattleEncounter();

    //void ShowDlg();

private:
    CTerrain* m_pTerrain;

    DWORD m_dwCurTileIdx;
    DWORD m_dwNextTileIdx;
    TILE* m_pCurTile;
    TILE* m_pUpTile;
    TILE* m_pDownTile;
    TILE* m_pLeftTile;
    TILE* m_pRightTile;

    _vec3 m_vDstTilePos;
    _vec3 m_vTileMoveDir;
    const float m_fTileMoveDefaultSpeed;
    float m_fTileMoveSpeed;

    //bool m_bIsHillMove;
    //bool m_bIsMoveOutside;

    //enum EFFECTS { ENTERGRASS, ARROWDOWN, SCREEN, EFFECTS_END };
    //CObj* m_arrEffects[EFFECTS_END];

    //enum MENU_UI { MAIN, POKeMON, BAG, MENU_UI_END };
    //CObj* m_arrMenuUI[MENU_UI_END];
    //bool m_bShowMenu;
    //MENU_UI m_eCurUI;
    //// Menu : POKEDEX = 0, POKEMON, INVENTORY, PLAYER, REPORT, SETTING, CLOSE = 6
    //// POKeMON : 0 부터 포켓몬, 마지막에 cancel
    //DWORD m_dwPreUICmd;
    //DWORD m_dwCurUICmd;
    //DWORD m_dwPreUIDepth;
    //DWORD m_dwCurUIDepth;
    //DWORD m_dwSelectUICmd;

    //bool m_bBattleEncounter;           // 인카운트 걸렸을 때부터
    //float m_fBattleReadyTime;
    //DWORD m_dwFieldIDPreBattle;

    //// 포켓몬
    //vector<POKeINFO*> m_vecPokemon;
    //DWORD m_dwPokemonCnt;

    //// 아이템
    //vector<ITEMINFO*> m_vecItems;
    //vector<ITEMINFO*> m_vecKeyItems;
    //vector<ITEMINFO*> m_vecPokeBalls;

    //// NPC 대화
    //bool m_bNPCDlg;
    //DWORD m_dwNPCDlgIdx;
    //DWORD m_dwNPCDlgPhase;
    //bool m_bDlgWaiting;
    //float m_fMoveTime;
    //const float DLG_ARROW_MOVE_DEFAULT;
    //float m_fMoveOffset;
    //float m_fDlgNullPosTime;
    //bool m_bDlgEnd;

    //WCHAR m_szFirstLine[64];
    //WCHAR m_szSecondLine[64];

    //enum { DIALOG, DIALOG_ARROW, DLG_FIRSTLINE, DLG_SECONDLINE, DLG_END };
    //struct UI_POS
    //{
    //    bool isUsing;
    //    _vec3 vPos;
    //};
    //UI_POS m_arrUIPos[DLG_END];

    //DWORD m_dwEventID;

};


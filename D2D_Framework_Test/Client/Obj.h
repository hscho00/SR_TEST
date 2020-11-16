#pragma once

class CObj abstract
{
public:
	CObj();								// 가장 처음 초기화 할 때
	virtual ~CObj() = default;

public:
	virtual HRESULT Init() PURE;		// 초기값 재 셋팅 용도(다시 호출될 수 있음)
	virtual OBJ::EVENT Update() PURE;
	virtual void LateUpdate() PURE;
	virtual void Render() PURE;

protected:
	virtual void Release() PURE;

	virtual void FrameMove();

public:
	OBJ::ID Get_ID() const { return m_ObjID; }

	OBJ::RENDER_GROUP Get_RenderGroup() const { return m_RenderGroup; }
	void Set_RenderGroup(OBJ::RENDER_GROUP group) { m_RenderGroup = group; }

	bool IsUsing() const { return m_bUsing; }
	virtual void Set_Using(bool bUsing) { m_bUsing = bUsing; }		// Terrain Overrided

	bool IsDead() const { return m_bDead; }
	void Set_Dead(bool bDead) { m_bDead = bDead; }

	bool IsDraw() const { return m_bDraw; }
	void Set_Draw(bool bDraw) { m_bDraw = bDraw; }

	const _vec3& Get_Pos() const { return m_vPos; }
	virtual void Set_Pos(const _vec3& pos) { m_vPos = pos; }		// PopUpUI Overrided

	void Set_ObjectKey(const WCHAR* pObjKey) { m_pObjectKey = pObjKey; }
	void Set_StateKey(const WCHAR* pStateKey) { m_pStateKey = pStateKey; }
	const WCHAR* Get_StateKey() const { return m_pStateKey; }
	
	virtual void Set_Frame(const FRAME& frame) { m_frame = frame; }	// ScreenEffect Overrided
	FRAME& Get_Frame() { return m_frame; }	// UI Frame 수정용...

	void Set_Dir(OBJ::DIR dir) { m_eDir = dir; }

protected:
	OBJ::ID m_ObjID;
	OBJ::RENDER_GROUP m_RenderGroup;
	
	bool m_bUsing;	// false면 update 시 바로 빠져 나감
	bool m_bDead;	
	bool m_bDraw;	// false면 render X

	_vec3 m_vPos;
	_vec3 m_vSize;

	const WCHAR* m_pObjectKey;
	const WCHAR* m_pStateKey;
	FRAME m_frame;

	OBJ::DIR m_eDir;

};


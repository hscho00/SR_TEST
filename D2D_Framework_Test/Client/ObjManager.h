#pragma once

class CObj;

class CObjManager
{
	DECLARE_SINGLETON(CObjManager)

private:
	CObjManager() = default;
	~CObjManager();

public:
	void Init_ObjMgr(SCENE::ID eID);
	void Update_ObjMgr();
	void LateUpdate_ObjMgr();
	void Render_ObjMgr();

private:
	void Release();

public:
	HRESULT Add_Object(CObj* pObj, OBJ::ID id);
	HRESULT Delete_Objects(OBJ::ID id);
	
	CObj* Get_ObjOrNull(OBJ::ID id, int idx);
	CObj* Get_ObjOrNull(OBJ::ID id, const wstring& wstrStateKey, bool isNotUsing = false);

private:
	vector<CObj*> m_vecObj[static_cast<unsigned int>(OBJ::ID::END)];
	vector<CObj*> m_vecRenderSort[static_cast<unsigned int>(OBJ::RENDER_GROUP::END)];

};


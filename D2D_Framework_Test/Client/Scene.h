#pragma once

class CObjManager;
class CObj;

class CScene abstract
{
public:
	CScene();
	virtual ~CScene() = default;

public:
	virtual HRESULT Ready_Scene() PURE;
	virtual void Update_Scene() PURE;
	virtual void LateUpdate_Scene() PURE;
	virtual void Render_Scene() PURE;

protected:
	virtual void Release_Scene() PURE;

public:
	enum FIELD_ID { FIELD_0, FIELD_END };
	void Set_Field(FIELD_ID eID, bool isInit = true) { m_eCurField = eID; m_bIsInit = isInit; }
	void Set_Field(DWORD eID, bool isInit = true) { m_eCurField = (FIELD_ID)eID; m_bIsInit = isInit; }

	const FIELD_ID Get_FieldID() const { return m_eCurField; }

protected:
	virtual void ChangeField() PURE;
	void Set_UsingAllInField(FIELD_ID eID, bool bFlag, bool bInit);

protected:
	CObjManager* m_pObjMgr;

	FIELD_ID	m_ePreField;
	FIELD_ID	m_eCurField;

	vector<CObj*> m_vecObjInField[FIELD_END];

	bool m_bIsInit;

};


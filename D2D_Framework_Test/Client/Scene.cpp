#include "stdafx.h"
#include "Scene.h"
#include "ObjManager.h"
#include "Obj.h"


CScene::CScene()
	: m_pObjMgr(CObjManager::Get_Instance())
	, m_ePreField(FIELD_END)
	, m_eCurField(FIELD_END)
	, m_bIsInit(true)
{

}

void CScene::Set_UsingAllInField(FIELD_ID eID, bool bFlag, bool bInit)
{
	if (eID == FIELD_END || m_vecObjInField[eID].empty())
		return;

	for (auto& pObj : m_vecObjInField[eID])
	{
		if (bInit)
		{
			pObj->Init();
			pObj->Set_Dead(!bFlag);
		}
		pObj->Set_Using(bFlag);
	}
}

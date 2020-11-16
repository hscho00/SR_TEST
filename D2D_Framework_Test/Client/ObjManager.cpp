#include "stdafx.h"
#include "ObjManager.h"

#include "obj.h"

IMPLEMENT_SINGLETON(CObjManager)

CObjManager::~CObjManager()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(OBJ::RENDER_GROUP::END); ++i)
    {
        m_vecRenderSort[i].clear();
        m_vecRenderSort[i].shrink_to_fit();
    }

    for (unsigned int i = 0; i < static_cast<unsigned int>(OBJ::ID::END); ++i)
    {
        for_each(m_vecObj[i].begin(), m_vecObj[i].end(), Safe_Delete<CObj*>);
        m_vecObj[i].clear();
        m_vecObj[i].shrink_to_fit();
    }
}

void CObjManager::Init_ObjMgr(SCENE::ID eID)
{
    Release();

    // + vector reserve
    switch (eID)
    {
    case SCENE::ID::STAGE_1:
        m_vecObj[static_cast<unsigned int>(OBJ::ID::TERRAIN)].reserve(5);
        m_vecObj[static_cast<unsigned int>(OBJ::ID::NPC)].reserve(6);
        m_vecObj[static_cast<unsigned int>(OBJ::ID::PLAYER)].reserve(1);
        m_vecObj[static_cast<unsigned int>(OBJ::ID::EFFECT)].reserve(16);
        m_vecObj[static_cast<unsigned int>(OBJ::ID::UI)].reserve(6);

        m_vecRenderSort[static_cast<unsigned int>(OBJ::RENDER_GROUP::BACKGROUND)].reserve(1);
        m_vecRenderSort[static_cast<unsigned int>(OBJ::RENDER_GROUP::GAMEOBJECT)].reserve(10);
        m_vecRenderSort[static_cast<unsigned int>(OBJ::RENDER_GROUP::EFFECT)].reserve(10);
        m_vecRenderSort[static_cast<unsigned int>(OBJ::RENDER_GROUP::UI)].reserve(10);
		m_vecRenderSort[static_cast<unsigned int>(OBJ::RENDER_GROUP::SCREEN_EFFECT)].reserve(1);

        break;
    }
}

void CObjManager::Update_ObjMgr()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(OBJ::ID::END); ++i)
    {
        for (auto& pObj : m_vecObj[i])
        {
            if (!pObj->IsUsing())
                continue;

            OBJ::EVENT event = pObj->Update();
            if (event == OBJ::EVENT::DEAD)
            {
                // + Dead Ani

                pObj->Init();
                pObj->Set_Dead(false);  // 다음에 사용될 때를 위해
                pObj->Set_Using(false);
            }
        }
    }
}

void CObjManager::LateUpdate_ObjMgr()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(OBJ::ID::END); ++i)
    {
        for (auto& pObj : m_vecObj[i])
        {
            if (!pObj->IsUsing())
                continue;

            pObj->LateUpdate();

            if (pObj->IsDraw())
            {
                unsigned int group = static_cast<unsigned int>(pObj->Get_RenderGroup());
                m_vecRenderSort[group].push_back(pObj);
            }
        }
    }
}

void CObjManager::Render_ObjMgr()
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(OBJ::RENDER_GROUP::END); ++i)
    {
        // sort 필요 없어서 list -> vector로 변경
        // if (i == static_cast<unsigned int>(OBJ::RENDER_GROUP::GAMEOBJECT))
        //    m_listRenderSort[i].sort(CompareY<CObj*>);

        for (auto& pObj : m_vecRenderSort[i])
        {
             //if (pObj->IsDraw())
                pObj->Render();
        }

        m_vecRenderSort[i].clear();
    }
}

void CObjManager::Release()
{
    // 날릴것만 날리자
    m_vecRenderSort[static_cast<unsigned int>(OBJ::ID::TERRAIN)].clear();
    m_vecRenderSort[static_cast<unsigned int>(OBJ::ID::TERRAIN)].shrink_to_fit();
   
    for (unsigned int i = 0; i < static_cast<unsigned int>(OBJ::ID::END); ++i)
    {
        for_each(m_vecObj[i].begin(), m_vecObj[i].end(), Safe_Delete<CObj*>);
        m_vecObj[i].clear();
        m_vecObj[i].shrink_to_fit();
    }
}

HRESULT CObjManager::Add_Object(CObj* pObj, OBJ::ID id)
{
    // reserve 주의!
    m_vecObj[static_cast<unsigned int>(id)].push_back(pObj);

    return S_OK;
}

HRESULT CObjManager::Delete_Objects(OBJ::ID id)
{
    unsigned int i = static_cast<unsigned int>(id);
    for_each(m_vecObj[i].begin(), m_vecObj[i].end(), Safe_Delete<CObj*>);
    m_vecObj[i].clear();
    m_vecObj[i].shrink_to_fit();

    return S_OK;
}

CObj* CObjManager::Get_ObjOrNull(OBJ::ID id, int idx)
{
    if (idx < 0 || idx > (int)(m_vecObj[(unsigned int)id].size() - 1))
        return nullptr;

    return m_vecObj[(unsigned int)id][idx];
}

CObj* CObjManager::Get_ObjOrNull(OBJ::ID id, const wstring& wstrStateKey, bool isNotUsing/*= false*/)
{
    // statekey 쓰는 obj만 검사
    if (id == OBJ::ID::TERRAIN)
        return nullptr;

    for (CObj* pObj : m_vecObj[(unsigned int)id])
    {
        if (pObj->Get_StateKey() == wstrStateKey)
        {
            if (!isNotUsing)
                return pObj;
            else
            {
                if (pObj->IsUsing())
                    continue;
                else
                    return pObj;
            }
                
        }
    }

    return nullptr;
}

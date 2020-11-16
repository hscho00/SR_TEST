#include "stdafx.h"
#include "Obj.h"
#include "TimeManager.h"

CObj::CObj()
	: m_ObjID(OBJ::ID::END)
	, m_RenderGroup(OBJ::RENDER_GROUP::END)
	, m_bUsing(true)
	, m_bDead(false)
	, m_bDraw(true)
	, m_vPos()
	, m_vSize(_vec3(1.f, 1.f, 0.f))
	, m_frame()
	, m_pObjectKey(nullptr)
	, m_pStateKey(nullptr)
	, m_eDir(OBJ::DIR::END)
{

}

void CObj::FrameMove()
{
	m_frame.fCurFrameTime += CTimeManager::Get_Instance()->Get_DeltaTime();

	if (m_frame.fCurFrameTime > m_frame.fResetFrameTime)
	{
		++m_frame.byCurFrame;
		if (m_frame.byCurFrame > m_frame.byEndFrame)
			m_frame.byCurFrame = 0;

		m_frame.fCurFrameTime = 0.f;
	}
}

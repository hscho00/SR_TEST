#pragma once
#include "GameObject.h"
class CPlayer;
class CPlayerBullet :
	public CGameObject
{
public:
	CPlayerBullet();
	virtual ~CPlayerBullet();



	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Relaese_GameObject() override;


public:
	void Set_Dir(bool _Dir) { m_bDir = _Dir; }
	void Image(const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame, bool _dir, float _y =0.f);
	
	void Image_Effect(const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame);
	void Image_Warlock(const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame, bool _dir);
	void FrameMove(float fSpeed = 1.f);
	void EffetFrame(float fSpeed = 1.f);
	void Fall_Skul();
	void Set_Fall() { m_bFall = true; }
	void Dead_Rect();
	void Ready_Rect();
public:
	_vec3		m_vPlayer;
	bool		m_bDir;
	float		m_fSpeed;
	float		m_fAngle;
	float		m_fTemp;
	float		m_fFallTime;
	bool        m_bFall;
};



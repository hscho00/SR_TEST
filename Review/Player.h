#pragma once

#include "GameObject.h"
#include "Key_Manager.h"
class CPlayer final : public CGameObject
{
	
private:
	explicit CPlayer();
public:
	virtual ~CPlayer();
		
public:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Ready_GameObject() override;
	virtual int Update_GameObject() override;
	virtual void Late_Update_GameObject() override;
	virtual void Render_GameObject() override;
	virtual void Relaese_GameObject() override;
public:
	BOOL Get_Dir() { return m_bDirCheck; }
public:
	void FrameMove(float fSpeed = 1.f);
	void EffectFrame(float fSpeed = 1.f);
public :
	static CPlayer* Create(float _x, float _y);
	void Free(); 
	void Image(P_STATE _eState,const wstring& wstrObjectKey, const wstring& wstrStateKey , float EndFrame, bool _dir);
	void Image(P_STATE _eState, const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame, bool _dir, float _y);
	void Image_Effect(SKILL_EFFECT _eState, const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame, bool _dir);
	void Image_Effect(SKILL_EFFECT _eState, const wstring& wstrObjectKey, const wstring& wstrStateKey, float EndFrame, bool _dir, float _x, float _y = 0.f);
	void OffSet();
public:
	int behavior();
	void Jumping();
	void Dash();
	void Skill_Pessive();
	void Skill_Amp();
	void SKill_WARLOCK();
	void Skul_Change();
	void Rect_Attack(P_STATE _State);
	void Hit();

	void Set_State(P_STATE _State) { m_State = _State; }
	void Set_Hit() { m_bHit = true; }
	



public:
	P_STATE m_State;
	float m_fFallPower;
	
	bool m_bJump;
	bool m_bFall;
	bool m_bJumpbutoon;
	bool m_bDash;
	bool m_bDoubleJump;
	bool m_bDoubleJumpButton;
	bool m_bPessive;
	bool m_bAmp;
	bool m_bWarlock_Skill;
	float m_fJumpOption;
	float m_fJumpPower;
	float m_fJumpTime;
	float m_fDoubleJump;
	float m_fDoubleJumpOption;
	float m_fDoubleJumpTime;
	float m_fFallTime;
	float m_fDashPower;
	float m_fy;
	float m_fAmptime;
	int	  m_iAttackCount;
	int	  m_iDashCount;
	int	  m_iDoubleJump;
	int	  m_iSkill_1_Count;
	int	  m_iAmp_Count;
	int   m_iPessive_Count;
	int   m_iWarlock_Charge;
	int	  m_iWarlock_Charge2;
	int   m_iA;
	float m_fTest;
	float m_fHitTime;
	bool  m_bHit;


	
	_vec3 m_vSkul_Pos;



private:
	template <typename T>
	CGameObject* Create_Skill(BOOL _Dir, SKUL _Skul)
	{
		return CAbstractFactory<T>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y, _Dir, _Skul);
	}
	template <typename T>
	CGameObject* Create_Attack(BOOL _Dir, SKUL _Skul)
	{
		return CAbstractFactory<T>::Create(m_tInfo.vPos.x, m_tInfo.vPos.y, _Dir, _Skul);
	}
	template <typename T>
	CGameObject* Create_Pessive(float _x, float _y)
	{
		return CAbstractFactory<T>::Create_Pessive(_x, _y);
	}

	template <typename T>
	CGameObject* Create_Skill(float _x, float _y,BOOL _Dir, SKUL _Skul, SKILL_EFFECT _Skill)
	{
		return CAbstractFactory<T>::Create_Skill(_x, _y, _Dir, _Skul, _Skill);
	}

	/***************/
	bool m_bEndAnim;


	


	

	/********************************************/
	/*map<CPlayer::STATE, BOOL> m_mapState;
	TSTRING m_tstrObjectKey;
	TSTRING m_tstrStateKey;
	void AnimationCheck();*/
	/********************************************/



	





};


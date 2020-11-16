#pragma once
#include "Game_Object.h"
class Portal :
	public GameObject
{
private:
	explicit Portal();

public:
	virtual ~Portal();

public:
	static Portal* Create(const _vec3& _pos, wstring _connected_stage_name);

public:
	virtual HRESULT Ready_Game_Object() override;
	virtual _Int Update_Game_Object() override;
	virtual void LateUpdate_Game_Object() override;
	virtual void Render_Game_Object() override;
	virtual void Release_Game_Object() override;

private:
	void Ready_Potal(const _vec3& _pos, const wstring _connected_stage_name);
	void RenderTexture();
	void RenderCollisionbox();

public:
	void CollisionBox_Update();

public:
	wstring Connected_stage_name_;

	vector<_vec2>	CollisionBox;
	
	wstring			obj_key_;
	wstring			state_key_;
};


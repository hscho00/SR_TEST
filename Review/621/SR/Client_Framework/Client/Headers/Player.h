#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"

USING(Engine)
class Player final : public GameObject
{
private:
	explicit Player(_lpd3dd9 pDevice);
	virtual	~Player() = default;

public:
	static Player* Create(_lpd3dd9);
	virtual GameObject* Clone(void* _pArg = nullptr) override;
	virtual void Free() override;

public:
	// GameObject을(를) 통해 상속됨
	virtual HRESULT ReadyGameObjectPrototype() override;
	virtual HRESULT ReadyGameObject(void* _pArg = nullptr) override;
	virtual _uint UpdateGameObject(DOUBLE _fDeltaTime) override;
	virtual _uint LateUpdateGameObject(DOUBLE _fDeltaTime) override;
	virtual HRESULT RenderGameObject() override;


};

#endif
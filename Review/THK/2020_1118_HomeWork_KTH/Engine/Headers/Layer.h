#pragma once
#ifndef __CLAYER_H__

#include "Base.h"

BEGIN(Engine)
class CLayer final : public CBase
{
public:
	CLayer();
	virtual ~CLayer() = default;

public:
	HRESULT AddGameObjectInLayer(class CGameObject* pGameObject);
	_uint   UpdateGameObject(float fDeltaTime);
	_uchar	LateUpdateGameObject(float fDeltaTime);
public:
	virtual void Free() override;
private:
	typedef list<class CGameObject*> GAMEOBJECTS;
	GAMEOBJECTS m_GameObjects; //게임 오브젝트들의 클론을 보관.
};
END
#define __CLAYER_H__
#endif // !__CLAYER_H__
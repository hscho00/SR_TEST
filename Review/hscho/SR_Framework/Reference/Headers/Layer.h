#pragma once
#ifndef __LAYER_H__

#include "Base.h"

BEGIN(Engine)
class CLayer final : public CBase
{
private:
	CLayer();
	virtual ~CLayer() = default;

public:
	HRESULT ReserveCloneContainer(_uint capacity);		// vector reserve. 이름 별로 맘에 안듦
	HRESULT AddGameObjectInLayer(class CGameObject* pGameObject);
	_uint UpdateGameObject(float fDeltaTime);
	_uint LateUpdateGameObject(float fDeltaTime);

	//
	CGameObject* GetObjOrNull(_uint idx) const;

	/////////////////////////////////
	// 렌더러 생기면 밖으로 빠질 것들
	HRESULT RenderGameObject();
	/////////////////////////////////

public:
	static CLayer* Create(_uint vecCapacity);
	virtual void Free() override;

private:
	typedef vector<class CGameObject*>	GAMEOBJECTS;
	GAMEOBJECTS	m_GameObjects;	/* 게임 오브젝트의 클론들을 보관 */

};
END

#define __LAYER_H__
#endif
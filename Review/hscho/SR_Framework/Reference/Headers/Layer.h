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
	HRESULT ReserveCloneContainer(_uint capacity);		// vector reserve. �̸� ���� ���� �ȵ�
	HRESULT AddGameObjectInLayer(class CGameObject* pGameObject);
	_uint UpdateGameObject(float fDeltaTime);
	_uint LateUpdateGameObject(float fDeltaTime);

	//
	CGameObject* GetObjOrNull(_uint idx) const;

	/////////////////////////////////
	// ������ ����� ������ ���� �͵�
	HRESULT RenderGameObject();
	/////////////////////////////////

public:
	static CLayer* Create(_uint vecCapacity);
	virtual void Free() override;

private:
	typedef vector<class CGameObject*>	GAMEOBJECTS;
	GAMEOBJECTS	m_GameObjects;	/* ���� ������Ʈ�� Ŭ�е��� ���� */

};
END

#define __LAYER_H__
#endif
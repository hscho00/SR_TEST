#pragma once
#ifndef __SCENEMANAGER_H__

#include "Base.h"
#include "Scene.h"

BEGIN(Engine)
class CSceneManager final : public CBase
{
	DECLARE_SINGLETON(CSceneManager)
	
private:
	CSceneManager();
	virtual ~CSceneManager() = default;

public:
	HRESULT SetUpCurrentScene(CScene* pNextScene);
	_uint UpdateScene();
	_uint LateUpdateScene();

public:
	virtual void Free() override;

private:
	CScene*	m_pCurrentScene;

};
END

#define __SCENEMANAGER_H__
#endif
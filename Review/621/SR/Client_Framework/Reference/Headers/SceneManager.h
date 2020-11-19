#pragma once
#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Base.h"
#include "Scene.h"

CODEBEGIN(Engine)
class SceneManager final : public CBase
{
	DECLARE_SINGLETON(SceneManager)

private:
	SceneManager();
	virtual ~SceneManager() = default;

public:
	HRESULT SetUpCurrentScene(_int iSceneID, Scene * pCurrentScene);
	_uint UpdateScene();
	_uint LateUpdateScene();

public:
	virtual void Free() override;

private:
	Scene* m_pCurrentScene = nullptr;
	_int  m_iSceneID = -1;
};
CODEEND

#endif



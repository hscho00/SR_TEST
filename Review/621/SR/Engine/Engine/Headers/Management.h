#pragma once
#ifndef __MANAGEMENT_H__
#define __MANAGEMENT_H__

#include "Base.h"
#include "GraphicDevice.h"
#include "SceneManager.h"

BEGIN(Engine)

class ENGINE_DLL Management final :
    public CBase
{
    DECLARE_SINGLETON(Management)

private:
    Management();
    virtual ~Management() = default;

public:
    /* For.General*/
    HRESULT ReadyEngine(HWND hWnd, _uint iWinCX, _uint iWinCY, DisplayMode eDisplaymode);
    _uint UpdateEngine();
    _uint RenderEngine();

public:
    /* For.GraphicDev */
    LPDIRECT3DDEVICE9 GetDevice();

public:
    /* For.SceneManager */
    HRESULT SetUpCurrentScene(_int iSceneID, Scene * pCurrentScene);

public:
    virtual void Free() override;
    static void ReleaseEngine();

private:
    GraphicDevice* m_pGraphic_Device = nullptr;
    SceneManager* m_pSceneManager = nullptr;

    _uint m_iUpdateEvent = 0;
};
END
#endif

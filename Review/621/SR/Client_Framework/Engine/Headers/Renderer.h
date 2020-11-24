#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Base.h"

CODEBEGIN(Engine)
class Renderer final :
    public CBase
{
    DECLARE_SINGLETON(Renderer)

private:
    explicit Renderer();
    virtual ~Renderer() = default;

public:
    static  Renderer* Create(_lpd3dd9 pDevice);
    virtual void Free() override;

public:
    BOOL    get_Setting() { return bSetting; }

public:
    HRESULT AddGameObjectInRenderer(RenderID Id, class GameObject* GameObject);
    HRESULT Render(HWND hWnd = nullptr);

private:
    HRESULT Ready_Renderer(_lpd3dd9 pDevice);
   
public:
    HRESULT RenderPriority();
    HRESULT RenderNoAlpha();
    HRESULT RenderAlpha();
    HRESULT RenderUi();

private:
    _lpd3dd9    m_pDevice = nullptr;

    typedef list<class GameObject*> GAMEOBJECTS;
    GAMEOBJECTS m_GameObjects[(_uint)RenderID::MAX];

    BOOL       bSetting = FALSE;
};
CODEEND

#endif


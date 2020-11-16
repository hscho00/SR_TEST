#pragma once
#include "Scene.h"

class CPlayer;

class CStage1 : public CScene
{
public:
    CStage1();
    virtual ~CStage1();

public:
    virtual HRESULT Ready_Scene() override;
    virtual void Update_Scene() override;
    virtual void LateUpdate_Scene() override;
    virtual void Render_Scene() override;

private:
    virtual void Release_Scene() override;

private:
    virtual void ChangeField() override;

private:
    void Init_Field_0();
    void Set_Field_0();

private:
    CPlayer* m_pPlayer;

};


#pragma once
#include "GameObject.h"

USING(Engine)
class Terrain :
    public GameObject
{
private:
    explicit Terrain(_lpd3dd9 pDevice);
    explicit Terrain(const Terrain& other);
    virtual ~Terrain() = default;

public:
    static Terrain* Create(_lpd3dd9 pDevice);
    virtual GameObject* Clone(void* _pArg = nullptr) override;
    virtual void Free() override;

public:
    virtual HRESULT ReadyGameObjectPrototype() override;
    virtual HRESULT ReadyGameObject(void* _pArg = nullptr) override;
    virtual _uint UpdateGameObject(DOUBLE _fDeltaTime) override;
    virtual _uint LateUpdateGameObject(DOUBLE _fDeltaTime) override;
    virtual HRESULT RenderGameObject() override;

private:
    HRESULT AddComponent();

private:
    class VIBuffer* m_pVIBufferCom = nullptr;
};


#pragma once
#ifndef __MAINAPP_H__

#include "Base.h"

USING(Engine)
class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT ReadyMainApp();
	_int UpdateMainApp();

private:
	HRESULT ReadyStaticResources();

public:
	static CMainApp* Create();
	virtual void Free() override;

private:
	CManagement* m_pManagement;
	LPDIRECT3DDEVICE9 m_pDevice;

};

#define __MAINAPP_H__
#endif
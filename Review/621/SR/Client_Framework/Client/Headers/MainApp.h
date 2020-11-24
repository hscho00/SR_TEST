#pragma once

#ifndef __MAINAPP_H__
#define __MAINAPP_H__

#include "Base.h"

USING(Engine)

class MainApp final : public CBase
{
private:
	MainApp();
	virtual ~MainApp() = default;

public:
	static MainApp* Create();
	virtual void Free() override;

public:
	HRESULT ReadyMainApp();
	int UpdateMainApp();

private:
	HRESULT	ReadyStaticResources();
	HRESULT ReadyDefaultSetting();

private:
	Management* m_pManagement = nullptr;
	_lpd3dd9	m_pDevice = nullptr;
};

#endif
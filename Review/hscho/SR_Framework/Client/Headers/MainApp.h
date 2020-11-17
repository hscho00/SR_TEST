#pragma once

#ifndef __MAINAPP_H__

#include "Base.h"

class CGraphic_Device;

class CMainApp final : public CBase
{
private:
	CMainApp();
	virtual ~CMainApp() = default;

public:
	HRESULT ReadyMainApp();
	int UpdateMainApp();

public:
	static CMainApp* Create();
	virtual void Free() override;

private:
	CGraphic_Device* m_pGraphicDevice;
};

#define __MAINAPP_H__
#endif
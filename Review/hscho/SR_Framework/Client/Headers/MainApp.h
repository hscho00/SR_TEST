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

public:
	static CMainApp* Create();
	virtual void Free() override;

private:
	CManagement* m_pManagement;

};

#define __MAINAPP_H__
#endif
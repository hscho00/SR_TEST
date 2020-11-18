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
	HRESULT ReadyMainApp();

public:
	int UpdateMainApp();

public:
	static MainApp* Create();
	virtual void Free() override;

private:
	Mangement* m_pManagement = nullptr;
};

#endif

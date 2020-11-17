#pragma once

#include "Base.h"

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
};

#pragma once

#include "EngineInclude.h"

class ENGINE_DLL CBase abstract
{
protected:
	CBase();
	virtual ~CBase() = default;

public:
	_uint	AddRef();
	_uint	Release();

protected:
	virtual void Free() = 0;

protected:
	_uint reference_count_ = 0;
};

#include "Base.h"

CBase::CBase()
{
}

_uint CBase::AddRef()
{
	return reference_count_++;
}

_uint CBase::Release()
{
	if (0 == reference_count_)
	{
		Free();
		delete this;
		return 0;
	}
	return reference_count_--;
}

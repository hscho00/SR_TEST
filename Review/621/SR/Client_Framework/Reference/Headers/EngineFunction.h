#pragma once
#ifndef __ENGINE_FUNCTION_H__
#define __ENGINE_FUNCTION_H__

template<typename T>
void SafeDelete(T& _ptr)
{
	if (_ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template<typename T>
void SafeDeleteArray(T& _ptr)
{
	if (_ptr)
	{
		delete[] _ptr;
		_ptr = nullptr;
	}
}

template<typename T>
_uint SafeAddref(T& _ptr)
{
	_uint	reference_count = 0;

	if (_ptr)
	{
		reference_count = ptr->AddRef();
	}

	return reference_count;
}

template<typename T>
_uint SafeRelease(T& _ptr)
{
	_uint	reference_count = 0;

	if (_ptr)
	{
		reference_count = _ptr->Release();

		if (0 == reference_count)
		{
			_ptr = nullptr;
		}
	}

	return reference_count;
}

#endif
#pragma once

template<typename T>
ULONG Safe_Release(T& rInstance)
{
	DWORD dwRefCnt = 0; 
	if (rInstance)
	{
		dwRefCnt = rInstance->Release(); 
		rInstance = nullptr;
		return dwRefCnt; 
	}
	return dwRefCnt; 
}

template<typename T>
void Safe_Delete(T& rInstance)
{
	if (rInstance)
	{
		delete rInstance; 
		rInstance = nullptr; 
	}
}

/*
template <typename T>
bool CompareY(T& _Dst, T& _Src)
{
	// юс╫ц
	//return (_Dst->Get_Info().fY + (_Dst->Get_Info().iHeight >> 1)) < (_Src->Get_Info().fY + ((_Src->Get_Info().iHeight >> 1)));
	return false;
}
*/
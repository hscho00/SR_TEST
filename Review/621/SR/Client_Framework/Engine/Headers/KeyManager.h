#pragma once
#ifndef __KEY_MANAGER_H__
#define __KEY_MANAGER_H__

#include "Base.h"

CODEBEGIN(Engine)
class KeyManager : public CBase
{
	DECLARE_SINGLETON(KeyManager)

public:
	enum KEY_STATE : DWORD
	{
		UP		= 0x00000001,
		DOWN	= 0x00000002,
		LEFT	= 0x00000004,
		RIGHT	= 0x00000008,
		RETURN	= 0x00000010,
		W		= 0x00000020,
		A		= 0x00000040,
		S		= 0x00000080,
		D		= 0x00000100,
		Q		= 0x00000200,
		E		= 0x00000400,
	};

public:
	KeyManager();
	virtual ~KeyManager() = default;

public:
	virtual void Free() override;

public:
	void	Update_KeyMgr();

	BOOL	IsKeyUp(KEY_STATE key);
	BOOL	IsKeyDown(KEY_STATE key);
	BOOL	IsKeyPressing(KEY_STATE key);

private:
	DWORD	m_dwCurKey;
	DWORD	m_dwKeyUp;
	DWORD	m_dwKeyDown;

};
CODEEND
#endif

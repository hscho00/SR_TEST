#pragma once

class CKeyManager
{
	DECLARE_SINGLETON(CKeyManager)

public:
	enum KEY_STATE : DWORD
	{
		UP		= 0x00000001,
		DOWN	= 0x00000002,
		LEFT	= 0x00000004,
		RIGHT	= 0x00000008,
		RETURN	= 0x00000010,
		Z		= 0x00000020,
		X		= 0x00000040,
		A		= 0x00000080,
		//S		= 0x00000100,
		NUM1	= 0x00000200,
		//NUM2	= 0x00000400,
		//NUM3	= 0x00000800,
		LSHIFT	= 0x00001000
	};

public:
	CKeyManager();
	~CKeyManager() = default;

public:
	void Update_KeyMgr();

	bool IsKeyUp(KEY_STATE key);
	bool IsKeyDown(KEY_STATE key);
	bool IsKeyPressing(KEY_STATE key);

private:
	DWORD m_dwCurKey;
	DWORD m_dwKeyUp;
	DWORD m_dwKeyDown;

};


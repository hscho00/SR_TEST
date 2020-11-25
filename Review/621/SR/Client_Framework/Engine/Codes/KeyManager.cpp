#include "..\Headers\KeyManager.h"


USING(Engine)

IMPLEMENT_SINGLETON(KeyManager)

KeyManager::KeyManager()
	: m_dwCurKey(0), m_dwKeyUp(0), m_dwKeyDown(0)
{
}

void KeyManager::Free()
{
}

void KeyManager::Update_KeyMgr()
{
	m_dwCurKey = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwCurKey |= UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwCurKey |= DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwCurKey |= LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwCurKey |= RIGHT;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwCurKey |= RETURN;
	if (GetAsyncKeyState('W') & 0x8000)
		m_dwCurKey |= W;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwCurKey |= A;
	if (GetAsyncKeyState('A') & 0x8000)
		m_dwCurKey |= S;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwCurKey |= D;
	if (GetAsyncKeyState('Q') & 0x8000)
		m_dwCurKey |= Q;
	if (GetAsyncKeyState('E') & 0x8000)
		m_dwCurKey |= E;

}

BOOL KeyManager::IsKeyUp(KEY_STATE key)
{
	if (m_dwCurKey & key)
	{
		m_dwKeyUp |= key;
		return false;
	}
	else if (m_dwKeyUp & key)
	{
		m_dwKeyUp ^= key;
		return true;
	}

	return false;
}

BOOL KeyManager::IsKeyDown(KEY_STATE key)
{
	if ((m_dwCurKey & key) && !(m_dwKeyDown & key))
	{
		m_dwKeyDown |= key;
		return true;
	}
	else if (!(m_dwCurKey & key) && (m_dwKeyDown & key))
	{
		m_dwKeyDown ^= key;
		return false;
	}

	return false;
}

BOOL KeyManager::IsKeyPressing(KEY_STATE key)
{
	if (m_dwCurKey & key)
		return true;

	return false;
}

#include "stdafx.h"
#include "KeyManager.h"

IMPLEMENT_SINGLETON(CKeyManager)

CKeyManager::CKeyManager()
	: m_dwCurKey(0), m_dwKeyUp(0), m_dwKeyDown(0)
{

}

void CKeyManager::Update_KeyMgr()
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
	if (GetAsyncKeyState('Z') & 0x8000)
		m_dwCurKey |= Z;
	if (GetAsyncKeyState('X') & 0x8000)
		m_dwCurKey |= X;
	if (GetAsyncKeyState('A') & 0x8000)
		m_dwCurKey |= A;
	//if (GetAsyncKeyState('S') & 0x8000)
	//	m_dwCurKey |= S;
	if (GetAsyncKeyState('1') & 0x8000)
		m_dwCurKey |= NUM1;
	//if (GetAsyncKeyState('2') & 0x8000)
	//	m_dwCurKey |= NUM2;
	//if (GetAsyncKeyState('3') & 0x8000)
	//	m_dwCurKey |= NUM3;
	if (GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		m_dwCurKey |= LSHIFT;
}

bool CKeyManager::IsKeyUp(KEY_STATE key)
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

bool CKeyManager::IsKeyDown(KEY_STATE key)
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

bool CKeyManager::IsKeyPressing(KEY_STATE key)
{
	if (m_dwCurKey & key)
		return true;

	return false;
}

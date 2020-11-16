#include "stdafx.h"
#include "ScrollManager.h"

_vec3 CScrollManager::m_vScroll = {};

DWORD CScrollManager::m_dwTerrainWidth = 0;
DWORD CScrollManager::m_dwTerrainHeight = 0;

BOOL CScrollManager::m_bLockScrollX = FALSE;
BOOL CScrollManager::m_bLockScrollY = FALSE;

float CScrollManager::Get_Scroll(SCROLL_ID eScrollID)
{
	switch (eScrollID)
	{
	case SCROLL_X:
		return m_vScroll.x;
	case SCROLL_Y:
		return m_vScroll.y;
	}
	return 0.0f;
}

void CScrollManager::Accumulate_Scroll(const _vec3& vAmount)
{
	if (!m_bLockScrollX)
		m_vScroll.x += vAmount.x;
	if (!m_bLockScrollY)
		m_vScroll.y += vAmount.y;
}

void CScrollManager::Accumulate_ScrollX(float fAmount)
{
	if (!m_bLockScrollX)
		m_vScroll.x += fAmount;
}

void CScrollManager::Accumulate_ScrollY(float fAmount)
{
	if (!m_bLockScrollY)
		m_vScroll.y += fAmount;
}

void CScrollManager::ScrollRock()
{
	if (m_dwTerrainWidth > WINCX)
	{
		if (m_vScroll.x < 0.f)
			m_vScroll.x = 0.f;
		else if (m_vScroll.x > (float)(m_dwTerrainWidth) - WINCX)
			m_vScroll.x = (float)(m_dwTerrainWidth) - WINCX;
	}

	if (m_dwTerrainHeight > WINCY)
	{
		if (m_vScroll.y < 0.f)
			m_vScroll.y = 0.f;
		else if (m_vScroll.y > (float)(m_dwTerrainHeight) - WINCY)
			m_vScroll.y = (float)(m_dwTerrainHeight) - WINCY;
	}
}

void CScrollManager::Init_Scroll(const DWORD terrainWidth, const DWORD terrainHeight)
{
	m_dwTerrainWidth = terrainWidth;
	m_dwTerrainHeight = terrainHeight;

	if (terrainWidth < WINCX)
	{
		m_vScroll.x = -float((WINCX >> 1) - (terrainWidth >> 1));
		m_bLockScrollX = TRUE;
	}
	else
		m_bLockScrollX = FALSE;

	if (terrainHeight < WINCY)
	{
		m_vScroll.y = -float((WINCY >> 1) - (terrainHeight >> 1));
		m_bLockScrollY = TRUE;
	}
	else
		m_bLockScrollY = FALSE;
}

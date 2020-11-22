#pragma once

#ifndef __ENGINE_ENUM_H__

BEGIN(Engine)
enum class EDisplayMode : BOOL
{
	Full = 0,
	Windowed = 1
};

enum class ERenderID : unsigned int
{
	Priority,
	NoAlpha,
	Alpha,
	UI,
	MaxCount
};
END

#define __ENGINE_ENUM_H__
#endif
#pragma once

#ifndef __ENGINE_ENUM_H__
#define __ENGINE_ENUM_H__

enum class DisplayMode : BOOL
{
	FULL,
	WINDOW
};

enum class RenderID : _uint
{
	PRIORITY,
	NOALPHA,
	ALPHA,
	UI,
	MAX
};

#endif
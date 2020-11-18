#pragma once

#ifndef __ENGINE_STRUCT_H__

struct Vertex
{
	Vertex() 
		: x(0.f), y(0.f), z(0.f), color(D3DCOLOR_ARGB(255, 255, 0, 0))
	{}

	Vertex(float _x, float _y, float _z, D3DCOLOR _color)
		: x(_x), y(_y), z(_z), color(_color)
	{}

	float x, y, z;	// ��ġ
	DWORD color;	// ����
	static const DWORD FVF;
};

#define __ENGINE_STRUCT_H__
#endif
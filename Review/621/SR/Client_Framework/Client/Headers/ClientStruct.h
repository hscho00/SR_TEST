#pragma once
#ifndef __CLIENT_STRUCT_H__
#define __CLIENT_STRUCT_H__

struct ColorVertex
{
	ColorVertex() {}
	ColorVertex(float x, float y, float z, D3DCOLOR color)
	{
		_x = x;
		_y = y;
		_z = z;
		_color = color;
	}
	float _x, _y, _z;
	D3DCOLOR _color;
	static const DWORD FVF;
};
const DWORD ColorVertex::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
#endif // !__CLIENT_STRUCT_H__

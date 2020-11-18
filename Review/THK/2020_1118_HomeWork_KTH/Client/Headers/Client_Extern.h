#pragma once

#ifndef __CLIENT_EXTERN_H__

extern HWND g_hWnd;



struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	float _x, _y, _z;
	static const DWORD FVF;
};

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

const DWORD Vertex::FVF = D3DFVF_XYZ;

#define __CLIENT_EXTERN_H__
#endif
#pragma once
#ifndef __ENGINE_STRUCT_H__
#define __ENGINE_STRUCT_H__

CODEBEGIN(Engine)

typedef struct tagVertexColor
{
	tagVertexColor()
		: vPosition(0.f,0.f,0.f), iColor(D3DCOLOR_ARGB(255, 255, 255, 255))
	{}

	tagVertexColor(float _x, float _y, float _z, _uint _color)
		: vPosition(_x, _y, _z), iColor(_color)
	{}
	
	D3DXVECTOR3 vPosition;
	_uint iColor;
} VTX_COLOR;

const _uint FVF_VTX_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct tagVertexTexture
{
	tagVertexTexture()
		: vPosition(0.f, 0.f, 0.f), vUV(0.f, 0.f)
	{}

	tagVertexTexture(float _x, float _y, float _z, float _u, float _v)
		: vPosition(_x, _y, _z), vUV(_u, _v)
	{}
	
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vUV;

} VTX_TEXTURE;

const _uint FVF_VTX_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

typedef struct tagIndex16
{
	WORD _1, _2, _3;
} INDEX16;

typedef struct tagIndex32
{
	DWORD _1, _2, _3;
} INDEX32;

CODEEND

#endif
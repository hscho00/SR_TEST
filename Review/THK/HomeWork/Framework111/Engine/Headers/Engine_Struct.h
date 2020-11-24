#pragma once

#ifndef __ENGINE_STRUCT_H__

BEGIN(Engine)

typedef struct tagVertexColor
{
	D3DXVECTOR3 vPosition;
	_uint iColor;
}VTX_COLOR;

const _uint FVF_VTX_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;

typedef struct tagVertexTexture
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vUV;
}VTX_TEXTURE;

const _uint FVF_VTX_TEXTURE = D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;

typedef struct tagIndex16
{
	WORD _1, _2, _3;
}INDEX16;

typedef struct tagIndex32
{
	DWORD _1, _2, _3;
}INDEX32;

END

#define __ENGINE_STRUCT_H__
#endif
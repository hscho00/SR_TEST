#pragma once

#ifndef __ENGINE_STRUCT_H__

BEGIN(Engine)

typedef struct tagVertexColor
{
	D3DXVECTOR3 vPosition;
	_uint iColor;
	static const _uint FVF;	// D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;	// TEX0 : 텍스쳐 사용 X
}VTX_COLOR;

typedef struct tagVertexTexture
{
	D3DXVECTOR3 vPosition;
	D3DXVECTOR2 vUV;
	static const _uint FVF;	// D3DFVF_XYZ | D3DFVF_TEX1 /*| D3DFVF_TEXCOORDSIZE2(0)*/;	// TEXCOORDSIZE2 : 2차원좌표(0번인덱스)
}VTX_TEXTURE;

END

#define __ENGINE_STRUCT_H__
#endif
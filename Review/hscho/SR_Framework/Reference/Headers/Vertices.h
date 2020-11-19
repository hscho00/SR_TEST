#pragma once
#ifndef __VERTICES_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CVertices final : public CBase
{
	///////////////// 나중에 VI 버퍼 컴포넌트로 갈것임~~~~~~~~~~~~~~~ /////////////////////////////

private:
	CVertices();
	virtual ~CVertices() = default;

private:
	HRESULT ReadyVertices(Vertex vertices[], _uint verticesCount, WORD indices[], _uint indicesCount, _uint primCount);

public:
	IDirect3DVertexBuffer9* Get_VertexBuffer() const { return m_pVertexBuffer; }
	IDirect3DIndexBuffer9* Get_IndexBuffer() const { return m_pIndexBuffer; }
	_uint Get_VerticesCount() const { return m_iVerticesCount; }
	_uint Get_PrimCount() const { return m_iPrimCount; }
	const DWORD Get_FVF() const { return Vertex::FVF; }

private:
	IDirect3DVertexBuffer9* m_pVertexBuffer;
	IDirect3DIndexBuffer9* m_pIndexBuffer;
	_uint m_iVerticesCount;
	_uint m_iPrimCount;

public:
	static CVertices* Create(Vertex vertices[], _uint verticesCount, WORD indices[], _uint indicesCount, _uint primCount);
	virtual void Free() override;

};
END

#define __VERTICES_H__
#endif
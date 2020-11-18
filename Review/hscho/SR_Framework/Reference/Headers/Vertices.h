#pragma once
#ifndef __VERTICES_H__

#include "Base.h"

BEGIN(Engine)
class ENGINE_DLL CVertices final : public CBase
{
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

	// 임시
	const _matrix& Get_MatWorld() const { return m_matWorld; }
	void Set_MatWorld(const _matrix& matWorld) { m_matWorld = matWorld; }

private:
	IDirect3DVertexBuffer9* m_pVertexBuffer;
	IDirect3DIndexBuffer9* m_pIndexBuffer;
	_uint m_iVerticesCount;
	_uint m_iPrimCount;

	// 임시
	_matrix m_matWorld;

public:
	static CVertices* Create(Vertex vertices[], _uint verticesCount, WORD indices[], _uint indicesCount, _uint primCount);
	virtual void Free() override;

};
END

#define __VERTICES_H__
#endif
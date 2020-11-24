#include "..\Headers\VIBuffer_TerrainColor.h"

USING(Engine)

VIBuffer_TerrainColor::VIBuffer_TerrainColor(_lpd3dd9 pDevice)
	: VIBuffer(pDevice)
{
}

VIBuffer_TerrainColor::VIBuffer_TerrainColor(const VIBuffer_TerrainColor& other)
	: VIBuffer(other)
	, Terrain_x(other.Terrain_x)
	, Terrain_y(other.Terrain_y)
{
}

VIBuffer_TerrainColor* VIBuffer_TerrainColor::Create(LPDIRECT3DDEVICE9 pDevice, _uint _terrain_x, _uint _terrain_y)
{
	VIBuffer_TerrainColor* pInstance = new VIBuffer_TerrainColor(pDevice);
	pInstance->SetSize(_terrain_x, _terrain_x);
	if (FAILED(pInstance->ReadyComponentPrototype()))
	{
		LOG_MSG(L"Error", L"VIBuffer_TerrainColor Creation has Failed");
		SafeRelease(pInstance);
	}

	return pInstance;
}

Component* VIBuffer_TerrainColor::Clone(void* pArg)
{
	VIBuffer_TerrainColor* pClone = new VIBuffer_TerrainColor(*this);
	if (FAILED(pClone->ReadyComponent(pArg)))
	{
		LOG_MSG(L"Error", L"VIBuffer_TerrainColor Clone has Failed");
		SafeRelease(pClone);
	}
	
	return pClone;
}

void VIBuffer_TerrainColor::Free()
{
	VIBuffer::Free();
}

HRESULT VIBuffer_TerrainColor::ReadyComponentPrototype()
{

	m_iVerticesSize = sizeof(VTX_COLOR);
	m_iVerticesCount = (Terrain_x + 1) * (Terrain_y + 1);	// CalaulateVerticesCount 버틱스 구하는 함수
	m_iFVF = FVF_VTX_COLOR;
	m_iPrimCount = (Terrain_x * Terrain_y) * 2; // 가로 세로 곱셈(정사각형으로 하자)

	m_iIndexSize = sizeof(INDEX16);
	m_IndexFormat = D3DFMT_INDEX16;

	if (FAILED(VIBuffer::ReadyComponentPrototype()))
	{
		E_FAIL;
	}

	CalaulateVerticesIndex();

	return S_OK;
}

HRESULT VIBuffer_TerrainColor::ReadyComponent(void* pArg)
{
	if (FAILED(VIBuffer::ReadyComponent(pArg)))
	{
		return E_FAIL;
	}
	
	
	return S_OK;
}

HRESULT VIBuffer_TerrainColor::Render_VIBuffer()
{
	if (FAILED(VIBuffer::Render_VIBuffer()))
		return E_FAIL;

	/* 장치에게 인덱스버퍼 셋 */
	if (FAILED(m_pDevice->SetIndices(m_pIndexBuffer)))
		return E_FAIL;

	return m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_iVerticesCount, 0, m_iPrimCount);
}

int VIBuffer_TerrainColor::CalaulateVerticesIndex()
{
	VTX_COLOR* pVertex = nullptr;
	m_pVertexBuffer->Lock(0, 0, (void**)&pVertex, 0);

	for (_uint i = 0; i <= Terrain_y; ++i)
	{
		for (_uint j = 0; j <= Terrain_x; ++j)
		{
			pVertex[ (Terrain_x+1)*i + j].vPosition = _vector3(float(j), 0.f, float(i));
			pVertex[(Terrain_x + 1) * i + j].iColor = D3DCOLOR_ARGB(255, 255, 0, 0);
		}
	}

	m_pVertexBuffer->Unlock();

	INDEX16* pIndex = nullptr;

	m_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);

	for (_uint i = 0; i < Terrain_y; ++i)
	{
		for (_uint j = 0; j < Terrain_x; ++j)
		{
			
			pIndex[(Terrain_x*2) * i + (j * 2)]._1 = (Terrain_x + 1)*(i+1) + j;						// 5
			pIndex[(Terrain_x*2) * i + (j * 2)]._2 = (Terrain_x + 1)*(i+1) + j+1;						// 6
			pIndex[(Terrain_x*2) * i + (j * 2)]._3 = (Terrain_x + 1)*(i) + j+1;		//1

			pIndex[(Terrain_x * 2) * i + (j * 2) + 1]._1 = (Terrain_x + 1) * (i + 1) + j;						// 5
			pIndex[(Terrain_x * 2) * i + (j * 2) + 1]._2 = (Terrain_x + 1) * (i)+ j + 1;				// 1
			pIndex[(Terrain_x * 2) * i + (j * 2) + 1]._3 = (Terrain_x + 1) * (i)+ j;			//0
		}
	}

	m_pIndexBuffer->Unlock();

	// 삼각형의 총 수 4*4 *2
	// 32;

	/*
	24		26		28		30
		25		27		29		31
	16		18		20		22
		17		19		21		23
	8		10		12		14
		9		11		13		15
	0		2		4		6	
		1		3		5		7		
	*/

	/*
	20	21	22	23	24
	15	16	17	18	19
	10	11	12	13	14
	5	6	7	8	9
	0	1	2	3	4
	*/

	return 0;
}

void VIBuffer_TerrainColor::SetSize(_uint _terrain_x, _uint _terrain_y)
{
	Terrain_x = _terrain_x;
	Terrain_y = _terrain_y;
}

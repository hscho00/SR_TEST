#include "stdafx.h"
#include "Multi_Texture.h"
#include "Graphic_Device.h"


CMulti_Texture::CMulti_Texture()
{

}

CMulti_Texture::~CMulti_Texture()
{
    Release();
}

//..\Texture\Stage\Player\Stand\AKIHA_AKI00_00%d.png
HRESULT CMulti_Texture::Insert_Texture(const wstring& wstrFilePath, const wstring& wstrStateKey, const DWORD& dwCount)
{
    if (dwCount < 1)
        return E_FAIL;

    auto& iter_find = m_mapMultiTex.find(wstrStateKey);
	
	if (iter_find != m_mapMultiTex.end())
		return E_FAIL;

    m_mapMultiTex[wstrStateKey].reserve(dwCount);

    for (DWORD i = 0; i < dwCount; ++i)
    {
        TEXINFO* pTexInfo = new TEXINFO;
        ZeroMemory(pTexInfo, sizeof(TEXINFO));

		TCHAR szFileFullPath[MAX_PATH] = L"";
		swprintf_s(szFileFullPath, wstrFilePath.c_str(), i);

        if (FAILED(D3DXGetImageInfoFromFile(szFileFullPath, &pTexInfo->tImageInfo)))
        {
            delete pTexInfo;
            Release();

            return E_FAIL;
        }

        //
        if (FAILED(D3DXCreateTextureFromFileEx(CGraphic_Device::Get_Instance()->Get_Device(),
			szFileFullPath,
            pTexInfo->tImageInfo.Width,
            pTexInfo->tImageInfo.Height,
            pTexInfo->tImageInfo.MipLevels,
            0,
            pTexInfo->tImageInfo.Format,
            D3DPOOL_MANAGED,
            D3DX_DEFAULT,
            D3DX_DEFAULT,
            0,
            nullptr,
            nullptr,
            &pTexInfo->pTexture)))
        {
            ERR_MSG(L"Create Texture Failed! - MultiTexture.cpp");

            delete pTexInfo;
            Release();

            return E_FAIL;
        }

        m_mapMultiTex.find(wstrStateKey)->second.push_back(pTexInfo);
    }
    
    return S_OK;
}

const TEXINFO* CMulti_Texture::Get_TexInfo(const wstring& wstrStateKey, const DWORD& dwIndex)
{
	auto& iter_find = m_mapMultiTex.find(wstrStateKey);
	if (m_mapMultiTex.end() == iter_find)
		return nullptr;
	if (iter_find->second.size() <= dwIndex || 0 > dwIndex)
		return nullptr;

    return iter_find->second[dwIndex];
}

void CMulti_Texture::Release()
{
    for (auto& rPair : m_mapMultiTex)
    {
        for (auto& pTexInfo : rPair.second)
        {
            Safe_Release(pTexInfo->pTexture);
            Safe_Delete(pTexInfo);
        }

        rPair.second.clear();

		//rPair.second.swap(vector<TEXINFO*>()); 
		rPair.second.shrink_to_fit();
    }

    m_mapMultiTex.clear();
}

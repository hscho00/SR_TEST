#pragma once
#include "Texture.h"

class CMulti_Texture final : public CTexture
{
public:
	CMulti_Texture();
	virtual ~CMulti_Texture();

public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath, const wstring& wstrStateKey, const DWORD& dwCount) override;
	virtual const TEXINFO* Get_TexInfo(const wstring& wstrStateKey, const DWORD& dwIndex) override;
	virtual void Release() override;

private:
	map<wstring, vector<TEXINFO*>> m_mapMultiTex;

};


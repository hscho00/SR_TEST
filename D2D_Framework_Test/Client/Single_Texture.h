#pragma once
#include "Texture.h"

class CSingle_Texture final : public CTexture
{
public:
	CSingle_Texture();
	virtual ~CSingle_Texture();

public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath, const wstring& wstrStateKey = L"", const DWORD& dwCount = 0) override;
	virtual const TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"", const DWORD& dwIndex = 0) override;
	virtual void Release() override;

private:
	TEXINFO m_tTexInfo; 

};


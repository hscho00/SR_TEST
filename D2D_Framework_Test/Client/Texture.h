#pragma once
class CTexture abstract
{
public:
	explicit CTexture() = default;
	virtual ~CTexture() = default;

public:
	virtual HRESULT Insert_Texture(const wstring& wstrFilePath,
		const wstring& wstrStateKey = L"",
		const DWORD& dwIndex = 0) PURE;

	virtual const TEXINFO* Get_TexInfo(const wstring& wstrStateKey = L"",
		const DWORD& dwCount = 0) PURE; 

	virtual void Release() PURE; 

};


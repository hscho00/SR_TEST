#pragma once
class CGraphic_Device final
{
public:
	enum WINMODE { MODE_FULL, MODE_WINDONED };

public:
	static CGraphic_Device* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CGraphic_Device;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CGraphic_Device* m_pInstance;

private:
	explicit CGraphic_Device();
	virtual ~CGraphic_Device();

public:
	LPDIRECT3DDEVICE9	Get_Device() const { return m_pDevice; }
	LPD3DXSPRITE		Get_Sprite() const { return m_pSprite; }
	//LPD3DXSPRITE		Get_SubSprite() const { return m_pSubSprite; }

	LPD3DXFONT			Get_Font()				const { return m_pFont; }
	LPD3DXFONT			Get_DlgFont()			const { return m_pDlgFont; }
	LPD3DXFONT			Get_BattleInfoFont()	const { return m_pBattleInfoFont; }
	LPD3DXFONT			Get_BattleInfoNumFont()	const { return m_pBattleInfoNumFont; }

	LPD3DXLINE			Get_Line()	 const { return m_pLine; }
	
public:
	HRESULT Ready_Graphic_Device(WINMODE eWinMode);
	void Release_Graphic_Device();
	void Render_Begin();
	void Render_End(HWND _hWnd = nullptr);

private:
	LPDIRECT3D9			m_pSDK; 
	LPDIRECT3DDEVICE9	m_pDevice; 

	LPD3DXSPRITE	m_pSprite; 
	//LPD3DXSPRITE	m_pSubSprite;
	
	LPD3DXFONT		m_pFont;
	LPD3DXFONT		m_pDlgFont;
	LPD3DXFONT		m_pBattleInfoFont;
	LPD3DXFONT		m_pBattleInfoNumFont;

	LPD3DXLINE		m_pLine;

};


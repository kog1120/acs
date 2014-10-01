#pragma once

class GCFont 
{
public :
	GCFont(LPDIRECT3DDEVICE9 D3DDevice);
	GCFont();

	bool InitFont(char* font, int Width, int Height);
	float GetFPS();
	void ShowText(char *str, int x, int y, D3DCOLOR color);
	void ShowFPS(int x, int y, D3DCOLOR color);

protected:
	LPDIRECT3DDEVICE9		D3DDevice;


	LPD3DXFONT				m_FontObject;
};
#pragma once

#include "GCInclude.h"

class CGCFont {
public :
	CGCFont(LPDIRECT3DDEVICE9 D3DDevice);
	CGCFont();

public :
	LPDIRECT3DDEVICE9		D3DDevice;

private :
	LPD3DXFONT				m_FontObject;
public :
	bool InitFont(TCHAR* font, int Width, int Height);
	float GetFPS();
	void ShowText(TCHAR* str, int x, int y, D3DCOLOR color);
	void ShowFPS(int x, int y, D3DCOLOR color);
};
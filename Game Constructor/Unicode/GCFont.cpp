#include "GCFont.h"
//==================================================================================================
// ¢Â CGCWindow()
// Desc : »ý¼ºÀÚ
//==================================================================================================
CGCFont::CGCFont(LPDIRECT3DDEVICE9 D3DDevice)
{
	this->D3DDevice = D3DDevice;
}

CGCFont::CGCFont()
{
}

bool CGCFont::InitFont(TCHAR* font, int Width, int Height)
{
	HRESULT hr;
	
	hr = D3DXCreateFont(this->D3DDevice, Height, Width, 500, 0, false, DEFAULT_CHARSET, 0, 0, 0, font, &m_FontObject);
	
	if(FAILED(hr)) {
		return false;
	}
	return true;
}


void CGCFont::ShowText(char *str, int x, int y, D3DCOLOR color)
{
	RECT rect;
	rect.left	= x;
	rect.right	= 640;
	rect.top	= y;
	rect.bottom	= 480;
	
	m_FontObject->DrawTextA(NULL, str, -1, &rect, DT_LEFT | DT_EXPANDTABS, color);
}


void CGCFont::ShowFPS(int x, int y, D3DCOLOR color)
{
	static unsigned int start = 0;
	static unsigned int end   = 0;
	
	char buf[100];
	
	end = timeGetTime();
	sprintf(buf,"FPS : %3.3f", (float) 1000 / (end - start));
	
	ShowText(buf, x, y, color);
	
	start = end;
}
#pragma once

#include "GCInclude.h"

class CGCWindow {
public :
	CGCWindow();
	CGCWindow(HINSTANCE hInstance);

public :
	HWND					hwnd;

protected :
	HINSTANCE				m_hInstance;
	wchar_t*				m_Title;
	int						m_Width, m_Height;
	WNDPROC					m_WndProc;
	RECT					m_Rect, m_ChildRect;
	ULONG					m_Cursor;
	double					m_prev_time;
	D3DXCOLOR				m_Color;

public :
	LPDIRECT3DDEVICE9		D3DDevice;
protected :
	LPDIRECT3D9				m_D3DObject;

public :
	int Create(wchar_t* Title, ULONG Icon, int width, int height, int mode, bool duplication);
	int Create(wchar_t* Title, ULONG Icon, int width, int height, int mode, bool duplication, WNDPROC WndProc);

protected :
	bool InitWindow(int mode, ULONG Icon, bool duplication);
	bool InitDirectX(int mode);

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public :
	int Render(void (*render)(void));
	int Render(void (*render)(void), RECT* rt);

public :
	double GetFPS();
};
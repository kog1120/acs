#pragma once
//==================================================================================================
//
// ▣ GCWindow.h
//
//   Name : GCWindow
//   Desc : GC에서 윈도우에 관련된거 전부다 초기화 해준다.
//
//   Defined by : JH.K
//   Lasted 2011.10.31 15:04
//
//==================================================================================================
class GCWindow 
{
public :
	GCWindow(void);
	GCWindow(HINSTANCE hInstance);
	virtual ~GCWindow();

private:
	void Initialize();
	int Delete();

public :
	int SetRenderColor(GCCOLOR color);
	int SetGraphicMode(int mode); // 2D, 3D 선택
	int Create(char* Title, ULONG Icon, int Width, int Height, int mode, bool duplication);
	int Create(char* Title, ULONG Icon, int Width, int Height, int mode, bool duplication, WNDPROC WndProc);

protected:
	bool InitWindow(int mode, ULONG Icon, bool duplication);
	bool InitDirectX(int Width, int Height, int mode);

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
	int Render(void (*render)(void));
	int Render(void (*render)(void), RECT* rt);

	double GetFPS();

	LPDIRECT3DDEVICE9 GetDevice(void);

	void ShowMousePoint(int show);

protected :
	HWND					_hwnd;

	HINSTANCE				_hInstance;
	const char*				_Title;
	int						_Width, _Height;
	WNDPROC					_WndProc;
	RECT					_Rect, _ChildRect;
	ULONG					_Cursor;
	double					_Prev_time;

	D3DXCOLOR				_Color;
	int						_nGraphicMode;

	LPDIRECT3DDEVICE9		_lpDXDevice;
	LPDIRECT3D9				_lpDXObject;
};
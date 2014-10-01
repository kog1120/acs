#pragma once

class GC3DGraphic
{
public:

};

/*

//, m_ChildWnd(NULL), m_D3DObject(NULL), m_D3DDevice(NULL), m_pVB(NULL), m_Texture(NULL),
//	m_FontObject(NULL), m_MaskColor(0, 0, 0, 255), m_Color(0, 0, 0, 255), m_bState(TRUE),
//	create_child(NULL)







bool CGCCore::CreateChildWindow(GEDevice Device, char* Title, int x, int y, int Width, int Height)
{
	this->m_hwnd = Device.m_hwnd;
	this->m_D3DDevice = Device.m_D3DDevice;

	WNDCLASS WndClass;
	WndClass.style = CS_CLASSDC;
	WndClass.lpfnWndProc = ChildProc;
	WndClass.cbClsExtra       = 0;
	WndClass.cbWndExtra       = 0;
	WndClass.hInstance        = m_hInstance;
	WndClass.hIcon = LoadIcon(m_hInstance, NULL);
	WndClass.hCursor          = LoadCursor(NULL, MAKEINTRESOURCE(m_Cursor));
	WndClass.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName     = NULL;
	WndClass.lpszClassName    = "Child";
	RegisterClass(&WndClass);

	this->m_ChildWnd = CreateWindowEx(0, "Child", Title, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CHILD | WS_CAPTION | WS_SYSMENU, x, y, Width,
		Height+27, m_hwnd, 0, this->m_hInstance, NULL);

	if(!this->m_ChildWnd) {
		MessageBox(this->m_hwnd, "윈도우 생성의 실패 했습니다.", "", 0);
		return FALSE;
	}

	GetClientRect(m_ChildWnd, &m_ChildRect);
	//윈도우 작성
	ShowWindow(this->m_ChildWnd, SW_SHOW);
	UpdateWindow(this->m_ChildWnd);
	UnregisterClass("Child", WndClass.hInstance);

//	AlphaBlend()
	// 투명윈도우
//	BYTE byTrans = 128; // 0 - 255 
//	LONG lOldStyle; 
//	const DWORD WS_EX_LAYERED = 0x80000; 
//	const DWORD LWA_ALPHA = 0X2; 
//	typedef BOOL (_stdcall *API_TYPE)(HWND,COLORREF,BYTE,DWORD); 
	
//	API_TYPE SetLayeredWindowAttributes; 
	
//	HMODULE hUser32 = ::GetModuleHandle("user32.dll"); 
	
//	SetLayeredWindowAttributes = (API_TYPE)::GetProcAddress(hUser32, "SetLayeredWindowAttributes"); 
	
//	if(SetLayeredWindowAttributes) 
//	{ 
//		lOldStyle = GetWindowLong(m_ChildWnd, GWL_EXSTYLE); 
//		SetWindowLong(m_ChildWnd, GWL_EXSTYLE, lOldStyle | WS_EX_LAYERED); 
//		SetLayeredWindowAttributes(m_ChildWnd, 0, byTrans, LWA_ALPHA); 
//	} 

	return TRUE;
}



void CGCCore::SetCursor(const int cursor)
{ // 커서아이디
	HCURSOR hCur;
	this->m_Cursor = cursor;
	hCur = LoadCursor(m_hInstance, MAKEINTRESOURCE(cursor));
	SetClassLong(m_hwnd, GCL_HCURSOR, (LONG)hCur);
}

void CGCCore::LoadMenu(const int lpMenuName)
{
	HMENU hMenu = NULL;
	if(hMenu != NULL) DestroyMenu(hMenu);
	hMenu = ::LoadMenu(this->m_hInstance, MAKEINTRESOURCE(lpMenuName));
	SetMenu(this->m_hwnd, hMenu);
}


void CGCCore::LoadMenu(HINSTANCE hInstance, const int lpMenuName)
{
	HMENU hMenu = NULL;
	if(hMenu != NULL) DestroyMenu(hMenu);
	hMenu = ::LoadMenu(hInstance, MAKEINTRESOURCE(lpMenuName));
	SetMenu(this->m_hwnd, hMenu);
}

void CGCCore::SetPosition(float x, float y, float z)
{ // x좌표, y좌표, z좌표
	m_x = x;
	m_y = y;
	m_z = z;
}






LRESULT CALLBACK CGCCore::ChildProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	CGCCore core;
	HDC hdc, memDC;
	switch(msg) { 
		case WM_CREATE:
			if(core.create_child != NULL) {
				core.create_child();
			}
			break;
		case WM_ERASEBKGND:
			hdc = (HDC)wParam;
			memDC = CreateCompatibleDC(hdc);
			//::AlphaBlend(memDC, 
			break;
		case WM_KEYDOWN:
			if(core.m_bState == TRUE) {
				switch(wParam) {
					case VK_ESCAPE:
						return false;
				}
			}
			break;
		
		case WM_DESTROY: 
			break;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

GEDevice CGCCore::GetDevice()
{
	GEDevice device;
	device.m_hwnd = this->m_hwnd;
	device.m_hInstance = this->m_hInstance;
	device.m_D3DDevice = this->m_D3DDevice;

	return device;
}



void CGCCore::ReFresh()
{
	this->m_D3DDevice->Present(NULL, NULL, NULL, NULL);
}

void CGCCore::ReFresh(RECT* rt)
{
	this->m_D3DDevice->Present(NULL, rt, NULL, NULL);
}

void CGCCore::Delete()
{
}
*/
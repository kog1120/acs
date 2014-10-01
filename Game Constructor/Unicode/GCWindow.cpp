#include "GCWindow.h"

static CGCWindow* g_pCGWnd;
//==================================================================================================
// ◈ CGCWindow()
// Desc : 생성자
//==================================================================================================
// hInstance : 윈도우 인스턴스핸들
//==================================================================================================
CGCWindow::CGCWindow(HINSTANCE hInstance) : hwnd(NULL), m_hInstance(hInstance), m_prev_time(0), m_D3DObject(NULL),
	D3DDevice(NULL)
{
	g_pCGWnd = this;
}

CGCWindow::CGCWindow()
{
}

//==================================================================================================
// ◈ Init()
// Desc : 윈도우생성 및 DirectX초기화
//==================================================================================================
// Title		 : 프로그램이름
// Icon			 : 프로그램에 사용할 아이콘
// width, height : 윈도우의 넓이, 높이
// mode			 : 윈도우모드(0 창모드, 1 전체화면, 2 팝업)
// duplication   : 중복기동여부
// hInstance     : 윈도우 인스턴스핸들
//==================================================================================================
int CGCWindow::Create(wchar_t* Title, ULONG Icon, int width, int height, int mode, bool duplication)
{
	this->m_Title  = Title;
	this->m_Width  = width;
	this->m_Height = height;

	m_WndProc = CGCWindow::WndProc;

	
	if(InitWindow(mode, Icon, duplication)==FALSE)
		MessageBoxW(NULL, _T("Window Create Failed"), _T(""), 0);
	if(InitDirectX(mode)==FALSE)
		MessageBoxW(NULL, _T("Init DirectX Failed"), _T(""), 0);

	return TRUE;
}

//==================================================================================================
// WndProc		 : 윈도우프로시저
//==================================================================================================
int CGCWindow::Create(wchar_t* Title, ULONG Icon, int width, int height, int mode, bool duplication, WNDPROC WndProc)
{
	this->m_Title  = Title;
	this->m_Width  = width;
	this->m_Height = height;

	m_WndProc = WndProc;

	if(InitWindow(mode, Icon, duplication)==FALSE) 
		MessageBox(NULL, _T("Window Create Failed"), _T(""), 0);
	if(InitDirectX(mode)==FALSE)
		MessageBox(NULL, _T("Init DirectX Failed"), _T(""), 0);

	return TRUE;
}

//==================================================================================================
// ◈ InitWindow()
// Desc : 윈도우생성
//==================================================================================================
// hInstance   : 윈도우 힌스턴스핸들
// mode        : 윈도우모드(0 창모드, 1 전체화면, 2 팝업)
// Icon		   : 프로그램에 사용할 아이콘
// duplication : 중복기동여부
//==================================================================================================
bool CGCWindow::InitWindow(int mode, ULONG Icon, bool duplication)
{
	// 중복기동
	if(duplication == FALSE) if(FindWindow(m_Title, NULL) != NULL) return FALSE;
	
	WNDCLASS WndClass;
	WndClass.style		      = CS_CLASSDC;
	WndClass.lpfnWndProc      = m_WndProc;
	WndClass.cbClsExtra       = 0;
	WndClass.cbWndExtra       = 0;
	WndClass.hInstance        = this->m_hInstance;
	if(Icon == 0) WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	else WndClass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(Icon));
	WndClass.hCursor          = LoadCursor(NULL, IDC_ARROW);
	m_Cursor = 32512;
	WndClass.hbrBackground    = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName     = NULL;
	WndClass.lpszClassName    = m_Title;
	RegisterClass(&WndClass);
	
	if(mode == 0) {
		this->hwnd = CreateWindowEx(0, m_Title, m_Title, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, m_Width,
					m_Height+27, NULL, NULL, this->m_hInstance, NULL);
	}
	else if(mode == 1) {
		this->hwnd = CreateWindowEx(WS_EX_TOPMOST, m_Title, m_Title, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN), NULL, NULL, this->m_hInstance, NULL);
	}
	else if(mode == 2) {
		this->hwnd = CreateWindowEx(0, m_Title, m_Title, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, m_Width,
					m_Height, NULL, NULL, this->m_hInstance, NULL);
	}

	if(!this->hwnd) {
		MessageBoxA(this->hwnd, "윈도우 생성의 실패 했습니다.", "", 0);
		return FALSE;
	}

	GetClientRect(hwnd, &m_Rect);
	
	//윈도우 작성
	ShowWindow(this->hwnd, SW_SHOW);
	UpdateWindow(this->hwnd);
	UnregisterClass(m_Title, WndClass.hInstance);

	return TRUE;
}

//==================================================================================================
// ◈ InitDirectX()
// Desc : DirectX초기화
//==================================================================================================
// mode : 윈도우모드(0 창모드, 1 전체화면, 2 팝업)
//==================================================================================================
bool CGCWindow::InitDirectX(int mode)
{
	D3DPRESENT_PARAMETERS d3dppApp;
	D3DDISPLAYMODE dmode;
	D3DLIGHT9 light;

	this->m_D3DObject = Direct3DCreate9(D3D_SDK_VERSION);
	if(this->m_D3DObject == NULL) return FALSE;
	
	// 현재의 디스플레이 모드를 얻는다
	if(FAILED(this->m_D3DObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode))) return FALSE;
	ZeroMemory(&d3dppApp, sizeof(d3dppApp));
	d3dppApp.hDeviceWindow = this->hwnd;
	if(m_Width > 800)  d3dppApp.BackBufferWidth  = 1024;
	else			 d3dppApp.BackBufferWidth  = m_Width;
	if(m_Height > 640) d3dppApp.BackBufferHeight = 768;
	else			 d3dppApp.BackBufferHeight = m_Height;
	d3dppApp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dppApp.BackBufferFormat		= dmode.Format;
	d3dppApp.BackBufferCount		= 1;

	if(mode == 1) {
		d3dppApp.Windowed				= FALSE;
		d3dppApp.EnableAutoDepthStencil = 1;
		d3dppApp.AutoDepthStencilFormat = D3DFMT_D16;
		
		// 디바이스의 작성
		if(FAILED(this->m_D3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dppApp, &this->D3DDevice))){
			if(FAILED(this->m_D3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dppApp, &this->D3DDevice))){
				MessageBoxW(this->hwnd, _T("다이렉트X 초기화의 실패 했습니다."), _T(""), 0);
				return FALSE;
			}
		}
	}
	else if(mode == 0 || mode == 2) {
		d3dppApp.Windowed					= TRUE;
		
		d3dppApp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		
		// 디바이스의 작성
		if(FAILED(this->m_D3DObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dppApp, &this->D3DDevice))) {
			MessageBoxW(this->hwnd, _T("다이렉트X 초기화의 실패 했습니다."), _T(""), 0);
			return FALSE;
		}
	}
	d3dppApp.EnableAutoDepthStencil = TRUE;
	d3dppApp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dppApp.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
	this->D3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	// 렌더링Color = Texture Color과 정점Color의 평균
	this->D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	this->D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	this->D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	
	// 알파치 = Texture 알파와 정점 알파의 평균
	this->D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	this->D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	this->D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient.r = 1.0f; light.Ambient.g = 1.0f; light.Ambient.b = 1.0f;
	light.Diffuse.r = 1.5f; light.Diffuse.g = 1.5f; light.Diffuse.b = 1.5f;
	light.Direction = D3DXVECTOR3(-1.0f, -1.0f, -0.2f);
	
	this->D3DDevice->SetLight(0, &light);
	this->D3DDevice->LightEnable(0, TRUE);

	return TRUE;
}

//==================================================================================================
// ◈ WndProc()
// Desc : 윈도우 프로시저
//==================================================================================================
// 생략
//==================================================================================================
LRESULT CALLBACK CGCWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg) { 
		case WM_USER+1:

			break;
		case WM_KEYDOWN:
			switch(wParam) {
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
			}
			break;	

		case WM_SIZE:
			break;
			
		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
	}
	
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//==================================================================================================
// ◈ Render()
// Desc : 화면 묘사
//==================================================================================================
// render : 실제 게임루프의 함수포인터
//==================================================================================================
int CGCWindow::Render(void (*render)(void))
{ // 렌더링할 함수
	MSG msg;
	#define FPS 16.6666666
//	#define FPS  8.3333333 // 120fps
	while(TRUE){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			if(timeGetTime() < this->m_prev_time)	{
				this->m_prev_time = timeGetTime();
			}
			
			double t = fabs(timeGetTime() - this->m_prev_time);
			
			if(t >= FPS) {
				do {							
					t -= FPS;
					this->m_prev_time += FPS;
				}
				while(t >= FPS);
				
				this->D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_Color, 1.0f, 0);
				this->D3DDevice->BeginScene();
				
				render();
				
				this->D3DDevice->EndScene();
				this->D3DDevice->Present(NULL, NULL, NULL, NULL);
			}
		}
	}
	return 0;
}
//==================================================================================================
// rt : 렌더링할 영역
//==================================================================================================
int CGCWindow::Render(void (*render)(void), RECT* rt)
{
	MSG msg;
	#define FPS 16.6666666
//	#define FPS  8.3333333 // 120fps
	while(TRUE){
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if(msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			if(timeGetTime() < this->m_prev_time)	{
				this->m_prev_time = timeGetTime();
			}
			
			double t = fabs(timeGetTime() - this->m_prev_time);
			
			if(t >= FPS) {
				do {							
					t -= FPS;
					this->m_prev_time += FPS;
				}
				while(t >= FPS);
				
				this->D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, m_Color, 1.0f, 0);
				this->D3DDevice->BeginScene();
				
				render();
				
				this->D3DDevice->EndScene();
				this->D3DDevice->Present(NULL, rt, NULL, NULL);
			}
		}
	}
	return 0;
}

//==================================================================================================
// ◈ GetFPS()
// Desc : 화면의 FPS를 얻는다.
//==================================================================================================
double CGCWindow::GetFPS()
{
	static unsigned int start = 0;
	static unsigned int end   = 0;
	
	float fps;

	end = timeGetTime();
	
	fps = ((float) 1000 / (end - start));
	
	start = end;

	return fps;
}
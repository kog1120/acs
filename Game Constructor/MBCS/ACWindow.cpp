#include "ACInclude.h"
#include "ACWindow.h"


static GCWindow* g_pCGWnd;
//==================================================================================================
// ◈ CGCWindow()
// Desc : 생성자
//==================================================================================================
// hInstance : 윈도우 인스턴스핸들
//==================================================================================================
GCWindow::GCWindow(HINSTANCE hInstance)
: _hInstance(NULL)
{
	g_pCGWnd = this;

	_hInstance = hInstance;
	
	_nGraphicMode = 0;

	Initialize();
}

GCWindow::GCWindow()
: _hInstance(NULL)
{
	g_pCGWnd = this;

	Initialize();
}

GCWindow::~GCWindow()
{
	Delete();
}

// 디폴트 칼라를 파란색으로 잡았음 풋
void GCWindow::Initialize()
{
	_hwnd = NULL;
	_Prev_time = 0;
	_lpDXObject = NULL;
	_lpDXDevice = NULL;
	_Color = D3DCOLOR_XRGB(0, 0, 255);
}

int GCWindow::Delete()
{
	return 0;
}


//==================================================================================================
// ◈ SetGraphicMode()
// Desc : 그래픽모드 결정, 2D 및 3D, 사용하지 않을시 기본 2D로 적용
//==================================================================================================
// mode			 : 그래픽모드(GC2D, GC3D)
//==================================================================================================
int GCWindow::SetGraphicMode(int mode)
{
	_nGraphicMode = mode;

	return 0;
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
int GCWindow::Create(char* Title, ULONG Icon, int Width, int Height, int mode, bool duplication)
{
	_Title  = Title;
	_Width  = Width;
	_Height = Height;

	_WndProc = GCWindow::WindowProc;

	if(InitWindow(mode, Icon, duplication)==FALSE)
		MessageBox(NULL, "Window Create Failed", "", 0);
	if(InitDirectX(Width, Height, mode)==FALSE)
		MessageBox(NULL, "Init DirectX Failed", "", 0);

	return TRUE;
}

//==================================================================================================
// WndProc		 : 윈도우프로시저
//==================================================================================================
int GCWindow::Create(char* Title, ULONG Icon, int Width, int Height, int mode, bool duplication, WNDPROC WndProc)
{
	_Title  = Title;
	_Width  = Width;
	_Height = Height;

	_WndProc = WindowProc;

	if(InitWindow(mode, Icon, duplication)==FALSE) 
		MessageBox(NULL, "Window Create Failed", "", 0);
	if(InitDirectX(Width, Height, mode)==FALSE)
		MessageBox(NULL, "Init DirectX Failed", "", 0);

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
bool GCWindow::InitWindow(int mode, ULONG Icon, bool duplication)
{
	// 중복기동
	if(duplication == FALSE) if(FindWindow(_Title, NULL) != NULL) return FALSE;
	
	WNDCLASS WndClass;
	WndClass.style		      = CS_CLASSDC;
	WndClass.lpfnWndProc      = _WndProc;
	WndClass.cbClsExtra       = 0;
	WndClass.cbWndExtra       = 0;
	WndClass.hInstance        = _hInstance;
	if(Icon == 0) WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	else WndClass.hIcon = LoadIcon(_hInstance, MAKEINTRESOURCE(Icon));
	WndClass.hCursor          = LoadCursor(NULL, IDC_ARROW);
	_Cursor = 32512;
	WndClass.hbrBackground    = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName     = NULL;
	WndClass.lpszClassName    = _Title;
	RegisterClass(&WndClass);
	
	if(mode == 0) {
		_hwnd = CreateWindowEx(0, _Title, _Title, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, _Width,
					_Height+27, NULL, NULL, _hInstance, NULL);
	}
	else if(mode == 1) {
		_hwnd = CreateWindowEx(WS_EX_TOPMOST, _Title, _Title, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN), NULL, NULL, _hInstance, NULL);
	}
	else if(mode == 2) {
		_hwnd = CreateWindowEx(0, _Title, _Title, WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, _Width,
					_Height, NULL, NULL, _hInstance, NULL);
	}

	if(!_hwnd) {
		MessageBox(_hwnd, "윈도우 생성의 실패 했습니다.", "", 0);
		return FALSE;
	}

	GetClientRect(_hwnd, &_Rect);
	
	//윈도우 작성
	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
	UnregisterClass(_Title, WndClass.hInstance);

	return TRUE;
}

//==================================================================================================
// ◈ InitDirectX()
// Desc : DirectX초기화
//==================================================================================================
// mode : 윈도우모드(0 창모드, 1 전체화면, 2 팝업)
//==================================================================================================
bool GCWindow::InitDirectX(int Width, int Height, int mode)
{
	D3DPRESENT_PARAMETERS d3dppApp;
	D3DDISPLAYMODE dmode;
	D3DLIGHT9 light;

	_lpDXObject = Direct3DCreate9(D3D_SDK_VERSION);
	
	if(_lpDXObject == NULL) return FALSE;
	
	// 현재의 디스플레이 모드를 얻는다
	if(FAILED(_lpDXObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dmode))) return FALSE;
	
	ZeroMemory(&d3dppApp, sizeof(d3dppApp));
	
	d3dppApp.hDeviceWindow = _hwnd;
	
	if(Width > 800)  d3dppApp.BackBufferWidth  = 1024;
	else				   d3dppApp.BackBufferWidth  = Width;
	if(Height > 640) d3dppApp.BackBufferHeight = 768;
	else				   d3dppApp.BackBufferHeight = Height;

	d3dppApp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dppApp.BackBufferFormat			= dmode.Format;
	d3dppApp.BackBufferCount			= 1;

	if(mode == 1) {
		d3dppApp.Windowed				= FALSE;
		d3dppApp.EnableAutoDepthStencil = 1;
		d3dppApp.AutoDepthStencilFormat = D3DFMT_D16;
		
		// 디바이스의 작성
		if(FAILED(_lpDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dppApp, &_lpDXDevice))){
			if(FAILED(_lpDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dppApp, &_lpDXDevice))){
				MessageBox(_hwnd, "다이렉트X 초기화의 실패 했습니다.", "", 0);
				return FALSE;
			}
		}
	}
	else if(mode == 0 || mode == 2) {
		d3dppApp.Windowed					= TRUE;
		
		d3dppApp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		
		// 디바이스의 작성
		if(FAILED(_lpDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dppApp, &_lpDXDevice))) {
			MessageBox(_hwnd, "다이렉트X 초기화의 실패 했습니다.", "", 0);
			return FALSE;
		}
	}
	d3dppApp.EnableAutoDepthStencil = TRUE;
	d3dppApp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dppApp.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
	_lpDXDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	// 렌더링Color = Texture Color과 정점Color의 평균
	_lpDXDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	_lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	
	// 알파치 = Texture 알파와 정점 알파의 평균
	_lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	_lpDXDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	
	ZeroMemory(&light, sizeof(D3DLIGHT9));
	
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient.r = 1.0f; light.Ambient.g = 1.0f; light.Ambient.b = 1.0f;
	light.Diffuse.r = 1.5f; light.Diffuse.g = 1.5f; light.Diffuse.b = 1.5f;
	light.Direction = D3DXVECTOR3(-1.0f, -1.0f, -0.2f);
	
	_lpDXDevice->SetLight(0, &light);
	_lpDXDevice->LightEnable(0, TRUE);

	return TRUE;
}

//==================================================================================================
// ◈ WndProc()
// Desc : 윈도우 프로시저
//==================================================================================================
// 생략
//==================================================================================================
LRESULT CALLBACK GCWindow::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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


int GCWindow::SetRenderColor(GCCOLOR color)
{
	return 0;
}
//==================================================================================================
// ◈ Render()
// Desc : 화면 묘사
//==================================================================================================
// render : 실제 게임루프의 함수포인터
//==================================================================================================
int GCWindow::Render(void (*render)(void))
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
			if(timeGetTime() < _Prev_time)	{
				_Prev_time = timeGetTime();
			}
			
			double t = fabs(timeGetTime() - _Prev_time);
			
			if(t >= FPS) {
				do {							
					t -= FPS;
					_Prev_time += FPS;
				}
				while(t >= FPS);
				
				_lpDXDevice->Clear(0, NULL, D3DCLEAR_TARGET, _Color, 1.0f, 0);
				_lpDXDevice->BeginScene();
				
				render();
				
				_lpDXDevice->EndScene();
				_lpDXDevice->Present(NULL, NULL, NULL, NULL);
			}
		}
	}
	return 0;
}
//==================================================================================================
// rt : 렌더링할 영역
//==================================================================================================
int GCWindow::Render(void (*render)(void), RECT* rt)
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
			if(timeGetTime() < _Prev_time)	{
				_Prev_time = timeGetTime();
			}
			
			double t = fabs(timeGetTime() - _Prev_time);
			
			if(t >= FPS) {
				do {							
					t -= FPS;
					_Prev_time += FPS;
				}
				while(t >= FPS);
				
				_lpDXDevice->Clear(0, NULL, D3DCLEAR_TARGET, _Color, 1.0f, 0);
				_lpDXDevice->BeginScene();
				
				render();
				
				_lpDXDevice->EndScene();
				_lpDXDevice->Present(NULL, rt, NULL, NULL);
			}
		}
	}
	return 0;
}

//==================================================================================================
// ◈ GetFPS()
// Desc : 화면의 FPS를 얻는다.
//==================================================================================================
double GCWindow::GetFPS()
{
	static unsigned int start = 0;
	static unsigned int end   = 0;
	
	float fps;

	end = timeGetTime();
	
	fps = ((float) 1000 / (end - start));
	
	start = end;

	return fps;
}


LPDIRECT3DDEVICE9 GCWindow::GetDevice(void)
{
	return _lpDXDevice;
}

void GCWindow::ShowMousePoint(int show)
{
	ShowCursor(show);

}
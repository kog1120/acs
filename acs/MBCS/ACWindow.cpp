#include "ACInclude.h"
#include "ACWindow.h"


static GCWindow* g_pCGWnd;
//==================================================================================================
// �� CGCWindow()
// Desc : ������
//==================================================================================================
// hInstance : ������ �ν��Ͻ��ڵ�
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

// ����Ʈ Į�� �Ķ������� ����� ǲ
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
// �� SetGraphicMode()
// Desc : �׷��ȸ�� ����, 2D �� 3D, ������� ������ �⺻ 2D�� ����
//==================================================================================================
// mode			 : �׷��ȸ��(GC2D, GC3D)
//==================================================================================================
int GCWindow::SetGraphicMode(int mode)
{
	_nGraphicMode = mode;

	return 0;
}



//==================================================================================================
// �� Init()
// Desc : ��������� �� DirectX�ʱ�ȭ
//==================================================================================================
// Title		 : ���α׷��̸�
// Icon			 : ���α׷��� ����� ������
// width, height : �������� ����, ����
// mode			 : ��������(0 â���, 1 ��üȭ��, 2 �˾�)
// duplication   : �ߺ��⵿����
// hInstance     : ������ �ν��Ͻ��ڵ�
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
// WndProc		 : ���������ν���
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
// �� InitWindow()
// Desc : ���������
//==================================================================================================
// hInstance   : ������ �����Ͻ��ڵ�
// mode        : ��������(0 â���, 1 ��üȭ��, 2 �˾�)
// Icon		   : ���α׷��� ����� ������
// duplication : �ߺ��⵿����
//==================================================================================================
bool GCWindow::InitWindow(int mode, ULONG Icon, bool duplication)
{
	// �ߺ��⵿
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
		MessageBox(_hwnd, "������ ������ ���� �߽��ϴ�.", "", 0);
		return FALSE;
	}

	GetClientRect(_hwnd, &_Rect);
	
	//������ �ۼ�
	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
	UnregisterClass(_Title, WndClass.hInstance);

	return TRUE;
}

//==================================================================================================
// �� InitDirectX()
// Desc : DirectX�ʱ�ȭ
//==================================================================================================
// mode : ��������(0 â���, 1 ��üȭ��, 2 �˾�)
//==================================================================================================
bool GCWindow::InitDirectX(int Width, int Height, int mode)
{
	D3DPRESENT_PARAMETERS d3dppApp;
	D3DDISPLAYMODE dmode;
	D3DLIGHT9 light;

	_lpDXObject = Direct3DCreate9(D3D_SDK_VERSION);
	
	if(_lpDXObject == NULL) return FALSE;
	
	// ������ ���÷��� ��带 ��´�
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
		
		// ����̽��� �ۼ�
		if(FAILED(_lpDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dppApp, &_lpDXDevice))){
			if(FAILED(_lpDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dppApp, &_lpDXDevice))){
				MessageBox(_hwnd, "���̷�ƮX �ʱ�ȭ�� ���� �߽��ϴ�.", "", 0);
				return FALSE;
			}
		}
	}
	else if(mode == 0 || mode == 2) {
		d3dppApp.Windowed					= TRUE;
		
		d3dppApp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		
		// ����̽��� �ۼ�
		if(FAILED(_lpDXObject->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dppApp, &_lpDXDevice))) {
			MessageBox(_hwnd, "���̷�ƮX �ʱ�ȭ�� ���� �߽��ϴ�.", "", 0);
			return FALSE;
		}
	}
	d3dppApp.EnableAutoDepthStencil = TRUE;
	d3dppApp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dppApp.Flags					= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	
	_lpDXDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	// ������Color = Texture Color�� ����Color�� ���
	_lpDXDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	_lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	_lpDXDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	
	// ����ġ = Texture ���Ŀ� ���� ������ ���
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
// �� WndProc()
// Desc : ������ ���ν���
//==================================================================================================
// ����
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
// �� Render()
// Desc : ȭ�� ����
//==================================================================================================
// render : ���� ���ӷ����� �Լ�������
//==================================================================================================
int GCWindow::Render(void (*render)(void))
{ // �������� �Լ�
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
// rt : �������� ����
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
// �� GetFPS()
// Desc : ȭ���� FPS�� ��´�.
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
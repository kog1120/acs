class ACWindow 
{
	public ACWindow()
	{
		return;
	}
	//GCWindow(HINSTANCE hInstance);
	public ~ACWindow()
	{
		return;
	}

	private void Initialize()
	{
	}
	private int Delete()
	{
		return 0;
	}

	public int SetRenderColor(GCCOLOR color)
	{
		return 0;
	}
	public int SetGraphicMode(int mode)
	{// 2D, 3D º±≈√
		return 0;
	}
	public int Create(String Title, ULONG Icon, int Width, int Height, int mode, bool duplication)
	{
		return 0;
	}
	public int Create(String Title, ULONG Icon, int Width, int Height, int mode, bool duplication, WNDPROC WndProc)
	{
		return 0;
	}


	protected bool InitWindow(int mode, ULONG Icon, bool duplication)
	{
		return 0;
	}
	protected bool InitDirectX(int Width, int Height, int mode)
	{
		return 0;
	}

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
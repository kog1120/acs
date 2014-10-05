/*
class CGCCore {
public:
	CGCCore();
	virtual ~CGCCore();


protected:
	HWND					m_hwnd, m_ChildWnd;

protected:
	HINSTANCE				m_hInstance;
	ULONG					m_Cursor;
	RECT					m_Rect, m_ChildRect;
	
protected:
	LPDIRECT3D9				m_D3DObject;
	LPDIRECT3DDEVICE9		m_D3DDevice;
	LPDIRECT3DTEXTURE9      m_Texture;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;


private:
	
	
	bool					m_bState;
	

protected: // Texture
	float m_x, m_y, m_z;
	typedef struct tag_GE_VERTEX{
		float	x, y, z, rhw;
		DWORD   color;
		float	tu, tv;
	} VERTEX, *LPVERTEX;
	D3DXCOLOR m_MaskColor;

public: // Basic Setting
	void SetInstance(HINSTANCE hInstance);
	void SetDevice(GCDevice Device);

public:	// Initialize
	bool CreateChildWindow(GCDevice Device, char* Title, int x, int y, int Width, int Height);

private:
	bool InitWindow(HINSTANCE hInstance, int mode, ULONG Icon, bool duplication);
	bool InitDirectX(int mode);

public:
//	inline void SetRenderColor(int nRed, int nGreen, int nBlue) { m_Color = D3DCOLOR_XRGB(nRed, nGreen, nBlue); }
//	inline void SetRenderColor(D3DCOLOR color) { m_Color = color; }
	

public: // Window
	void SetCursor(const int cursor);
	void LoadMenu(const int lpMenuName);
	void LoadMenu(HINSTANCE hInstance, const int lpMenuName);
	inline void SetKeyInput(bool bState) { m_bState = bState; }

public: // Texture
	void SetPosition(float x, float y, float z);
	inline void SetMaskColor(int nRed, int nGreen, int nBlue) { m_MaskColor = D3DCOLOR_XRGB(nRed, nGreen, nBlue); }
	inline void SetMaskColor(D3DCOLOR color) { m_MaskColor = color; }
	void DrawTexture(float x, float y, int u, int v, int w, int h);

public: // Font
	bool InitFont(char* font, int Width, int Height);
	void ShowText(char *str, int x, int y, D3DCOLOR color);
	void ShowFPS(int x, int y, D3DCOLOR color);
	float GetFPS();
	
private: // Window Procedure
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ChildProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public: // Get
	GCDevice GetDevice();

public: // Et Cetera
	void ReFresh();
	void ReFresh(RECT* rt);

private:
	void (*create_child)(void);
public:
	inline void SetCreate(void (*func)(void)){ create_child = func; }
};
*/
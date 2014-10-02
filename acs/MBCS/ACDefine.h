//==================================================================================================
//
// ▣ ACDefine.h
//
//   Desc : GC관련 Define 파일 정의 한거 없어도 무방.일지도..?
//
//   Defined by : JH.K
//   Lasted 2011.12.13 03:15
//
//==================================================================================================
#pragma once

//==================================================================================================
// ▣ Key constant value
//==================================================================================================
#define UPKEY    VK_UP					// Arrow UP
#define DOWNKEY  VK_DOWN				// Arrow DOWN
#define LEFTKEY  VK_LEFT				// Arrow LEFT
#define RIGHTKEY VK_RIGHT				// Arrow RIGHT

enum {
	KEYA = 0x0041,	// A Key
	KEYB = 0x0042,	// B Key
	KEYC = 0x0043,	// C Key
	KEYD = 0x0044,	// D Key
	KEYE = 0x0045,	// E Key
	KEYF = 0x0046,	// F Key
	KEYG = 0x0047,	// G Key
	KEYH = 0x0048,	// H Key
	KEYI = 0x0049,	// I Key
	KEYJ = 0x004A,	// J Key
	KEYK = 0x004B,	// K Key
	KEYL = 0x004C,	// L Key
	KEYN = 0x004D,  // N Key
	KEYM = 0x004E,	// M Key
	KEYO = 0x004F,	// O Key
	KEYP = 0x0050,	// P Key
	KEYQ = 0x0051,	// Q Key
	KEYR = 0x0052,	// R Key
	KEYS = 0x0053,	// S Key
	KEYT = 0x0054,	// T Key
	KEYU = 0x0055,	// U Key
	KEYV = 0x0056,	// V Key
	KEYW = 0x0057,	// W Key
	KEYX = 0x0058,	// X Key
	KEYY = 0x0059,	// Y Key
	KEYZ = 0x005A	// Z Key
};

#define F1KEY	 VK_F1					// F1 Key
#define F2KEY	 VK_F2					// F2 Key
#define F3KEY	 VK_F3
#define F4KEY	 VK_F4
#define F5KEY	 VK_F5

#define SPACEKEY VK_SPACE				// Spece Key
#define ESCKEY   VK_ESCAPE				// ESC Key


//==================================================================================================
// ▣ Graphic
//==================================================================================================
#define WINDOWMODE		0
#define FULLSCREEN		1
#define WINMODE			0
#define FULL			1

#define D3DBLEND_NORMAL 0	// 일반 알파 브랜드
#define	D3DBLEND_ADD	1	// 가산 알파 브랜드

//==================================================================================================
// ▣ Color Values
//==================================================================================================
#define BLACK				D3DCOLOR_XRGB(  0,   0,   0)
#define RED					D3DCOLOR_XRGB(255,   0,   0)
#define GREEN				D3DCOLOR_XRGB(  0, 255,   0)
#define BLUE				D3DCOLOR_XRGB(  0,   0, 255)
#define YELLOW				D3DCOLOR_XRGB(255, 255,   0)
#define SKYBLUE				D3DCOLOR_XRGB(  0, 255, 255)
#define PINK				D3DCOLOR_XRGB(255,   0, 255)
#define WHITE				D3DCOLOR_XRGB(255, 255, 255)
#define FREECOLOR(r, g, b)	D3DCOLOR_XRGB(r, g, b)
typedef D3DXCOLOR			GCCOLOR;

//==================================================================================================
// ▣ Event
//==================================================================================================
#define KEYDOWN			0
#define KEYUP			1



#define AC2D 0
#define AC3D 1

#define HIDE_MOUSE        0
#define SHOW_MOUSE		  1
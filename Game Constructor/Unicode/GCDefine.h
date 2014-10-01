//==================================================================================================
// GC관련 Define File 없어도 무방.
//==================================================================================================
#pragma once

#define UPKEY    VK_UP					// Arrow UP
#define DOWNKEY  VK_DOWN				// Arrow DOWN
#define LEFTKEY  VK_LEFT				// Arrow LEFT
#define RIGHTKEY VK_RIGHT				// Arrow RIGHT

//==================================================================================================
// ▣ Keyboard Key
//==================================================================================================
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
	KEYJ = 74,	// J Key
	KEYK = 75,	// K Key
	KEYL = 76,	// L Key
	KEYN = 77,  // N Key
	KEYM = 78,	// M Key
	KEYO = 79,	// O Key
	KEYP = 80,	// P Key
	KEYQ = 81,	// Q Key
	KEYR = 82,	// R Key
	KEYS = 83,	// S Key
	KEYT = 84,	// T Key
	KEYU = 85,	// U Key
	KEYV = 86,	// V Key
	KEYW = 87,	// W Key
	KEYX = 88,	// X Key
	KEYY = 89,	// Y Key
	KEYZ = 90	// Z Key
};

#define F1KEY	 VK_F1					// F1 Key
#define F2KEY	 VK_F2					// F2 Key
#define F3KEY	 VK_F3
#define F4KEY	 VK_F4
#define F5KEY	 VK_F5

#define SPACEKEY VK_SPACE				// Spece Key
#define ESCKEY   VK_ESCAPE				// ESC Key

#define WINDOWMODE		0
#define FULLSCREEN		1
#define WINMODE			0
#define FULL			1

#define KEYDOWN			0
#define KEYUP			1

//==================================================================================================
// ▣ GRAPHIC
//==================================================================================================
#define D3DBLEND_NORMAL 0	// 일반 알파 브랜드
#define	D3DBLEND_ADD	1	// 가산 알파 브랜드

//==================================================================================================
// ▣ Color Values
//==================================================================================================
#define BLACK D3DCOLOR_XRGB(  0,   0,   0)
#define WHITE D3DCOLOR_XRGB(255, 255, 255)
#define RED   D3DCOLOR_XRGB(255,   0,   0)
#define GREEN D3DCOLOR_XRGB(  0, 255,   0)
#define BLUE  D3DCOLOR_XRGB(  0,   0, 255)
#pragma once

#include "GCInclude.h"

class GCGraphic {
public :
	GCGraphic(LPDIRECT3DDEVICE9 D3DDevice);
	GCGraphic();

public :
	LPDIRECT3DDEVICE9		D3DDevice;

protected :

	typedef struct tag_GE_VERTEX{
		float	x, y, z, rhw;
		DWORD   color;
		float	tu, tv;
	} VERTEX, *LPVERTEX;

	LPDIRECT3DTEXTURE9      m_Texture;
	D3DXCOLOR				m_MaskColor;
	unsigned int m_ImgWidth, m_ImgHeight;
	float m_x, m_y, m_z;

	LPDIRECT3DVERTEXBUFFER9 m_pVB;

float	SprAngle ;					// 스프라이트 회전 각도
float	SprCenterX ;					// 스프라이트 회전, 확장 수축 중심
float	SprCenterY;					
float	SprScaleX;					// 스프라이트 스케일
float	SprScaleY;					



public :
	bool LoadTexture(char *Image);
	void DrawTexture(float x, float y, int u, int v, int width, int height);
};
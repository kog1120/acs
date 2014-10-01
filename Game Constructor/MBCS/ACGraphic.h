#pragma once

//====================================================================
//
// 2D �׷��� ����
//
//====================================================================

class GCGraphic 
{
public :
	GCGraphic(void);
	virtual ~GCGraphic(void);

	int Initialize(LPDIRECT3DDEVICE9 lpDXDevice);
	void Delete(void);

	HRESULT LoadSprite(char *src);
	void DrawSprite();


protected:
	LPDIRECT3DDEVICE9		_lpDXDevice;
	LPD3DXSPRITE			_lpDXSprite;
	LPDIRECT3DTEXTURE9		_lpDXTexture;
};
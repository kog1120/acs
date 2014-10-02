#include "ACInclude.h"
#include "ACGraphic.h"


GCGraphic::GCGraphic(void) 
{
	_lpDXSprite  = NULL;
	_lpDXTexture = NULL;
}

GCGraphic::~GCGraphic(void)
{
	Delete();
}

int GCGraphic::Initialize(LPDIRECT3DDEVICE9 lpDXDevice)
{
	_lpDXDevice = lpDXDevice;

	D3DXCreateSprite(_lpDXDevice, &_lpDXSprite);

	return 0;
}

void GCGraphic::Delete(void)
{
	if ( _lpDXTexture != NULL )
		 _lpDXTexture->Release();

	if ( _lpDXSprite != NULL )
		 _lpDXSprite->Release();
}


//==================================================================================================
// ¢Â LoadTexture()
// Desc : È­¸é ¹¦»ç
//==================================================================================================
HRESULT GCGraphic::LoadSprite(char *src)
{
	if( FAILED( D3DXCreateTextureFromFileEx(_lpDXDevice, src, D3DX_DEFAULT, D3DX_DEFAULT,1, 0, 
		D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, NULL, NULL, &_lpDXTexture)))
	{
		return E_FAIL;
	}

	return S_OK;
}



void GCGraphic::DrawSprite()
{
	RECT rc = { 0, 0, 257, 219 };

	_lpDXSprite->Begin(D3DXSPRITE_ALPHABLEND);

	_lpDXSprite->Draw(_lpDXTexture, &rc, NULL, NULL, 0xffffffff);

	_lpDXSprite->End();
}
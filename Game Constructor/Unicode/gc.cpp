#include "gc.h"

//==================================================================================================
// ¢Â CGCWindow()
// Desc : »ý¼ºÀÚ
//==================================================================================================
// Say Good bye~
GCDevice::GCDevice()
{
	this->m_hInstance = this->hInstance;
}

bool GCDevice::Init(char *Title, ULONG Icon, int width, int height, int mode, bool duplication)
{
	CGCWindow::Init(Title, Icon, width, height, mode, duplication);

	this->Graphic.D3DDevice = this->D3DDevice;
	this->Font.D3DDevice	= this->D3DDevice;
	return TRUE;
}
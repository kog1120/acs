#pragma once

#include "GCWindow.h"
#include "GCGraphic.h"
#include "GCFont.h"
#include "GCSound.h"
#include "GCDefine.h"

class GCDevice : public CGCWindow {
public :
	GCDevice();
	bool Init(char *Title, ULONG Icon, int width, int height, int mode, bool duplication);

public :
	HINSTANCE hInstance;

public :
	GCGraphic Graphic;
	CGCFont	   Font;
	CGCSound   Sound;
};

typedef GCDevice GCDEVICE, *LPGCDEVICE;
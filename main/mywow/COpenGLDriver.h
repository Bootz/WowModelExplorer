#pragma once

#include "base.h"
#include "IVideoDriver.h"

class COpenGLDriver : public IVideoDriver
{
public:
	COpenGLDriver();
	virtual ~COpenGLDriver();

public:
	bool initDriver(HWND hwnd, u32 adapter, bool fullscreen, bool vsync, u8 antialias, bool multithread);

public:
	virtual E_DRIVER_TYPE getDriverType() const { return EDT_OPENGL; }

public:
	//device settings
	HWND		HWnd;
	HDC		Hdc;

	CAdapterInfo	AdapterInfo;
	SDriverSetting	DriverSetting;
};


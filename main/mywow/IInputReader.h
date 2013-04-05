#pragma once

#include "base.h"

enum E_INPUT_DEVICE
{
	EID_KEYBOARD = 0,
	EID_MOUSE,
	EID_JOYSTICK,

	EID_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_MOUSE_BUTTON
{
	EMB_NONE = 0,
	EMB_LEFT = 1,
	EMB_RIGHT = 2,
	EMB_MIDDLE = 4,

	EMB_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

enum E_MODIFIER_KEY
{
	EMK_NONE = 0,
	EMK_SHIFT = 1,
	EMK_CTRL = 2,
	EMK_ALT = 4,
	EMK_LEFTMOUSE = 8,
	EMK_RIGHTMOUSE = 16,
	EMK_MIDDLEMOUSE = 32,

	EMK_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
};

class IInputListener
{
public:
	virtual ~IInputListener() {}

public:
	virtual void onKey(u8 key, bool down, E_MODIFIER_KEY modifier) = 0;
	virtual void onMouseButton(E_MOUSE_BUTTON button, bool down) = 0;
	virtual void onMouseMove(s32 x, s32 y) = 0;
};

class IInputReader
{
public:
	virtual ~IInputReader() {}

public:
	virtual bool acquire(E_INPUT_DEVICE device) = 0;
	virtual bool unacquire(E_INPUT_DEVICE device) = 0;
	virtual bool captureKeyboard() = 0;		//capture当前设备状态
	virtual bool captureMouse() = 0;
	virtual bool isKeyPressed(u8 keycode) = 0;
	virtual bool isMousePressed(E_MOUSE_BUTTON button) = 0;

	virtual void addListener(IInputListener* listener) = 0;
	virtual void removeListener(IInputListener* listener) = 0;
};
#pragma once

#include "core.h"
#include "IInputReader.h"
#include <map>
#include <list>

#define  KEYBOARD_BUFFERSIZE		8
#define  MOUSE_BUFFERSIZE	16

struct SDIKChar
{
	u8	dik;
	u8	key;
};

class CInputReader : public IInputReader
{
private:
	DISALLOW_COPY_AND_ASSIGN(CInputReader);

public: 
	CInputReader();
	~CInputReader();

public:
	virtual bool acquire(E_INPUT_DEVICE device);
	virtual bool unacquire(E_INPUT_DEVICE device);
	virtual bool captureKeyboard();		//capture当前设备状态
	virtual bool captureMouse();
	virtual bool isKeyPressed(u8 keycode);
	virtual bool isMousePressed(E_MOUSE_BUTTON button);

	virtual void addListener(IInputListener* listener);
	virtual void removeListener(IInputListener* listener);

	bool initDevice(HWND hwnd);

private:
	bool initializeKeyboard();
	bool initializeMouse();
	void releaseKeyboard();
	void releaseMouse();

private:
	HWND	HWnd;

	LPDIRECTINPUT8		pIDInput;
	LPDIRECTINPUTDEVICE8		pIDeviceKeyboard;
	LPDIRECTINPUTDEVICE8		pIDeviceMouse;

	u8	Diks[256];
	DIMOUSESTATE2		Dims2;
	u32		MouseButtons;

	E_MODIFIER_KEY		ModifierKey;

	typedef std::map<u8, u8, std::less<u8>, qzone_allocator<std::pair<u8, u8>>> T_DIK2CharMap;
	T_DIK2CharMap	DIK2CharMap;

	typedef std::map<u8, u8, std::less<u8>, qzone_allocator<std::pair<u8, u8>>> T_Char2DIKMap;
	T_Char2DIKMap	Char2DIKMap;

	typedef std::list<IInputListener*, qzone_allocator<IInputListener*>>		T_ListenerList;
	T_ListenerList	ListenerList;
};
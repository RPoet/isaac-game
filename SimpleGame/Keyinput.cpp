#include "stdafx.h"
#include "Keyinput.h"

int KeyIO::key[256];
int KeyIO::Initialize() {
	for (int i = 0; i < 256; ++i) {
		KeyIO::key[i] = KEY_UP_PERSIST;
	}
	return 0;
}

int KeyIO::update() {

	for (int i = 0; i < 256; ++i) {

		switch (KeyIO::key[i])
		{
			case KEY_UP_PERSIST:
				if (GetAsyncKeyState(i) & 0x8000) {
					KeyIO::key[i] = KEY_DOWN;
				}
				break;
			case KEY_DOWN:
				if (GetAsyncKeyState(i) & 0x8000) {
					KeyIO::key[i] = KEY_DOWN_PERSIST;
				}
				else {
					KeyIO::key[i] = KEY_UP;
				}
				break;
			case KEY_DOWN_PERSIST:
				if (GetAsyncKeyState(i) & 0x8000)
				{
					KeyIO::key[i] = KEY_DOWN_PERSIST;
				}
				else {
					KeyIO::key[i] = KEY_UP;
				}
				break;
			case KEY_UP:
				if (KeyIO::key[i] == KEY_UP) {
					if (GetAsyncKeyState(i) & 0x8000) {
						KeyIO::key[i] = KEY_UP;
					}
					else {
						KeyIO::key[i] = KEY_UP_PERSIST;
					}			
				}
			break;
		}
	}
	return 0;
}


void KeyIO::Exit() {

}
//지속키 검사
bool KeyIO::KeyState(int keycode) {
	switch (KeyIO::key[keycode])
	{
	case KEY_DOWN:
	case KEY_DOWN_PERSIST:
		return true;
		break;

	default:
		return false;
		break;
	}
}
//한번씩 끊어 검사 
bool KeyIO::KeyStateOnce(int keycode) {
	if (key[keycode] == KEY_DOWN) {
		return true;
	}
	else {
		return false;
	}
}
//떨어졌는지 검사
bool KeyIO::KeyStateUp(int keycode) {
	if (KeyIO::key[keycode] == KEY_UP || KeyIO::key[keycode] == KEY_UP_PERSIST) {
		return true;
	}
	else {
		return false;
	}
}

bool KeyIO::getAnyKeyDown() {
	for (int i = 1; i < 256; i++) {
		if (KeyIO::key[i] == KEY_DOWN) {
			return true;
		}

	}
	return false;
}

//void KeyIO::ReturnMousePos(int &mouse_x, int &mouse_y) {
//	 POINT mouse_coordinate;
//	 GetCursorPos(&mouse_coordinate);
//	 ScreenToClient(WINMAIN::g_hwnd, &mouse_coordinate);
//	mouse_x = ClippingInteger(0, WIDTH, mouse_coordinate.x);
//	mouse_y = ClippingInteger(0, HEIGHT, mouse_coordinate.y);
//}


#pragma once
#include <Windows.h>

enum keylist {
	KEY_UP_PERSIST, KEY_UP, KEY_DOWN_PERSIST, KEY_DOWN
};

class KeyIO {
	static int key[256];
public:
	static int Initialize();
	static int update();
	static void Exit();
	static bool KeyState(int keycode);
	static bool KeyStateOnce(int keycode);
	static bool getAnyKeyDown();
	static void ReturnMousePos(int &mouse_x, int &mouse_y);
	static bool KeyStateUp(int keycode);
};

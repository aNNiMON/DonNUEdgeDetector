#pragma once

#include <windows.h>
#include "WindowClass.h"

/**
 * Класс создания окна
 * @author aNNiMON
 */
class Window {
public:
	Window();

	void setClassName(LPCWSTR className);
	LPCWSTR getClassName();

	void setBounds(int x, int y, int w, int h);
	void setInstance(HINSTANCE hInstance);
	void setStyle(int style);
	void setTitle(LPCWSTR title);

	bool createWindow();
	HWND getWindow();

private:
	HWND hWnd;
	HINSTANCE hInstance;
	LPCWSTR title, className;
	int x, y, w, h;
	int style;
};



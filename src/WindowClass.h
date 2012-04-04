#pragma once

#include <windows.h>

/**
 * Класс регистрации WNDCLASS
 * @author aNNiMON
 */
class WindowClass {
public:
	WindowClass();

	bool registerClass();

	void setToDefault();
	void setBackgroundBrushColor(int color);
	void setCursor(HCURSOR hCursor);
	void setCursorType(LPCWSTR cursorType);
	void setClassName(LPCWSTR className);
	void setIcon(HICON hIcon);
	void setIconType(LPCWSTR iconType);
	void setInstance(HINSTANCE hInstance);
	void setMenuName(LPCWSTR menuName);
	void setStyle(int style);
	void setWindowProcedure(WNDPROC procedure);

	LPCWSTR getClassName();

private:
	WNDCLASS WndClass;
};


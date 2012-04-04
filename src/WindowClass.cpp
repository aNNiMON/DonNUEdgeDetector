#include "WindowClass.h"

/**
 * �����������.
 * ����� ��������� �� ��������.
 */
WindowClass::WindowClass() {
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	setToDefault();
}

/**
 * ����������� ������ ����.
 * return true - ����� ���������������, false - ��������� ������.
 */
bool WindowClass::registerClass() {
	if(!RegisterClass(&WndClass)) {
		MessageBox(NULL, L"���������� ���������������� �����", L"������", MB_OK);
		return false;
	}
	return true;
}

/**
 * ������ ��������� �� ��������.
 */
void WindowClass::setToDefault() {
	setStyle( CS_HREDRAW | CS_VREDRAW );
	setIconType(IDI_APPLICATION);
	setCursorType(IDC_ARROW);
	setBackgroundBrushColor(WHITE_BRUSH);
	setMenuName(L"MainMenu");
}

/**
 * ��������� ����� ����� ��� ���� ����.
 */
void WindowClass::setBackgroundBrushColor(int color) {
	WndClass.hbrBackground = (HBRUSH) GetStockObject(color);
}

/**
 * ��������� ����� ������.
 */
void WindowClass::setClassName(LPCWSTR className) {
	WndClass.lpszClassName = className;
}

/**
 * ��������� �������.
 */
void WindowClass::setCursor(HCURSOR hCursor) {
	WndClass.hCursor = hCursor;
}

/**
 * �������� � ��������� ������� �� ��� ����.
 */
void WindowClass::setCursorType(LPCWSTR cursorType) {
	setCursor( LoadCursor(NULL, cursorType) );
}

/**
 * ��������� ������.
 */
void WindowClass::setIcon(HICON hIcon) {
	WndClass.hIcon = hIcon;
}

/**
 * �������� � ��������� ������ �� � ����.
 */
void WindowClass::setIconType(LPCWSTR iconType) {
	setIcon( LoadIcon(NULL, iconType) );
}

/**
 * ��������� ����������� ����������.
 */
void WindowClass::setInstance(HINSTANCE hInstance) {
	WndClass.hInstance = hInstance;
}

/**
 * ������ ��� ����.
 */
void WindowClass::setMenuName(LPCWSTR menuName) {
	WndClass.lpszMenuName = menuName;
}

/**
 * ��������� �����.
 */
void WindowClass::setStyle(int style) {
	WndClass.style = style;
}

/**
 * ������� ������� ���������.
 */
void WindowClass::setWindowProcedure(WNDPROC procedure) {
	WndClass.lpfnWndProc = procedure;
}

/**
 * �������� ��� ������.
 */
LPCWSTR WindowClass::getClassName() {
	return WndClass.lpszClassName;
}

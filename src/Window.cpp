#include "Window.h"

/**
 * �����������.
 * ����� ����� � ������� ���� �� ��������.
 */
Window::Window() {
	x = CW_USEDEFAULT;
	y = CW_USEDEFAULT;
	w = CW_USEDEFAULT;
	h = CW_USEDEFAULT;
	style = WS_OVERLAPPEDWINDOW;
}

/**
 * ��������� ������ ����.
 */
void Window::setClassName(LPCWSTR className) {
	this->className = className;
}

/**
 * ��������� ������ ����.
 */
LPCWSTR Window::getClassName() {
	return className;
}

/**
 * ��������� ������� � ��������� ����.
 */
void Window::setBounds(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

/**
 * ��������� ����������� ����������.
 */
void Window::setInstance(HINSTANCE hInstance) {
	this->hInstance = hInstance;
}

/**
 * ��������� ����� ����.
 */
void Window::setStyle(int style) {
	this->style = style;
}

/**
 * ������� ��������� ����.
 */
void Window::setTitle(LPCWSTR title) {
	this->title = title;
}

/**
 * �������� ����.
 * ���������� ����� ������� ����������.
 * return true - ���� ������� �������, false - ��������� ������.
 */
bool Window::createWindow() {
	hWnd = CreateWindow(
		className, title, style,
		x, y, w, h,
		NULL, NULL,
		hInstance, NULL
	);

	if(!hWnd) {
		MessageBox(NULL, L"���������� ������� ����", L"������", MB_OK);
		return false;
	}
	return true;
}

/**
 * ��������� ����������� ����.
 */
HWND Window::getWindow() {
	return this->hWnd;
}
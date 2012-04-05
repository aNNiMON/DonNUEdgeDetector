#include "Window.h"

/**
 * Конструктор.
 * Задаёт стиль и размеры окна по умочанию.
 */
Window::Window() {
	x = CW_USEDEFAULT;
	y = CW_USEDEFAULT;
	w = CW_USEDEFAULT;
	h = CW_USEDEFAULT;
	style = WS_OVERLAPPEDWINDOW;
}

/**
 * Установка класса окна.
 */
void Window::setClassName(LPCWSTR className) {
	this->className = className;
}

/**
 * Получение класса окна.
 */
LPCWSTR Window::getClassName() {
	return className;
}

/**
 * Установка размера и положения окна.
 */
void Window::setBounds(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

/**
 * Установка дескриптора приложения.
 */
void Window::setInstance(HINSTANCE hInstance) {
	this->hInstance = hInstance;
}

/**
 * Установка стиля окна.
 */
void Window::setStyle(int style) {
	this->style = style;
}

/**
 * Задание заголовка окна.
 */
void Window::setTitle(LPCWSTR title) {
	this->title = title;
}

/**
 * Создание окна.
 * Вызывается после задания параметров.
 * return true - окно успешно создано, false - произошла ошибка.
 */
bool Window::createWindow() {
	hWnd = CreateWindow(
		className, title, style,
		x, y, w, h,
		NULL, NULL,
		hInstance, NULL
	);

	if(!hWnd) {
		MessageBox(NULL, L"Невозможно создать окно", L"Ошибка", MB_OK);
		return false;
	}
	return true;
}

/**
 * Получение дескриптора окна.
 */
HWND Window::getWindow() {
	return this->hWnd;
}
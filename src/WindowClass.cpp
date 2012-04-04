#include "WindowClass.h"

/**
 * Конструктор.
 * Задаёт параметры по умочанию.
 */
WindowClass::WindowClass() {
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	setToDefault();
}

/**
 * Регистрация класса окна.
 * return true - класс зарегистрирован, false - произошла ошибка.
 */
bool WindowClass::registerClass() {
	if(!RegisterClass(&WndClass)) {
		MessageBox(NULL, L"Невозможно зарегистрировать класс", L"Ошибка", MB_OK);
		return false;
	}
	return true;
}

/**
 * Задать параметры по умочанию.
 */
void WindowClass::setToDefault() {
	setStyle( CS_HREDRAW | CS_VREDRAW );
	setIconType(IDI_APPLICATION);
	setCursorType(IDC_ARROW);
	setBackgroundBrushColor(WHITE_BRUSH);
	setMenuName(L"MainMenu");
}

/**
 * Установка цвета кисти для фона окна.
 */
void WindowClass::setBackgroundBrushColor(int color) {
	WndClass.hbrBackground = (HBRUSH) GetStockObject(color);
}

/**
 * Установка имени класса.
 */
void WindowClass::setClassName(LPCWSTR className) {
	WndClass.lpszClassName = className;
}

/**
 * Установка курсора.
 */
void WindowClass::setCursor(HCURSOR hCursor) {
	WndClass.hCursor = hCursor;
}

/**
 * Загрузка и установка курсора по его типу.
 */
void WindowClass::setCursorType(LPCWSTR cursorType) {
	setCursor( LoadCursor(NULL, cursorType) );
}

/**
 * Установка иконки.
 */
void WindowClass::setIcon(HICON hIcon) {
	WndClass.hIcon = hIcon;
}

/**
 * Загрузка и установка иконки по её типу.
 */
void WindowClass::setIconType(LPCWSTR iconType) {
	setIcon( LoadIcon(NULL, iconType) );
}

/**
 * Установка дескриптора приложения.
 */
void WindowClass::setInstance(HINSTANCE hInstance) {
	WndClass.hInstance = hInstance;
}

/**
 * Задать имя меню.
 */
void WindowClass::setMenuName(LPCWSTR menuName) {
	WndClass.lpszMenuName = menuName;
}

/**
 * Установка стиля.
 */
void WindowClass::setStyle(int style) {
	WndClass.style = style;
}

/**
 * Задание оконной процедуры.
 */
void WindowClass::setWindowProcedure(WNDPROC procedure) {
	WndClass.lpfnWndProc = procedure;
}

/**
 * Получить имя класса.
 */
LPCWSTR WindowClass::getClassName() {
	return WndClass.lpszClassName;
}

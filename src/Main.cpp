#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <process.h>
#include "EdgeDetector.h"
#include "WindowClass.h"
#include "Window.h"
#include "resource.h"
#pragma comment(lib,"comctl32.lib")


LRESULT CALLBACK mainWindowProcedure(HWND, UINT, UINT, LONG);
void menuCommandSelected(HWND hWnd, UINT wParam);
void setPause(HWND hWnd, bool pause);
void setOperatorType(HWND hWnd, UINT type);
void setEffectTypes(HWND hWnd);

/** Состояния эффектов (включен / выключен) */
bool effectsEnabled[EFFECTS_END - EFFECTS_START + 1];
/** Детектор границ */
EdgeDetector detector;

bool pause, runningThread;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	// Регистрация класса окна
	WindowClass wClass = WindowClass();
	wClass.setToDefault();
	wClass.setInstance(hInstance);
	wClass.setClassName(L"DonNUEdgeDetector");
	wClass.setIconType(MAKEINTRESOURCE(IDI_ICON1));
	wClass.setMenuName(MAKEINTRESOURCE(IDR_MAINMENU));
	wClass.setWindowProcedure(mainWindowProcedure);
	if (!wClass.registerClass()) return 0;

	// Создание нового окна
	Window wnd = Window();
	wnd.setClassName(wClass.getClassName());
	wnd.setInstance(hInstance);
	wnd.setBounds(CW_USEDEFAULT, CW_USEDEFAULT, 400, 300);
	wnd.setTitle(wClass.getClassName());
	if (!wnd.createWindow()) return 0;
	
	// Загрузка таблицы акселераторов
	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_MAINACCELERATOR));

	// Отображение окна
	ShowWindow(wnd.getWindow(), nCmdShow);
	UpdateWindow(wnd.getWindow());
	DrawMenuBar(wnd.getWindow());

	detector.init(CV_CAP_ANY);

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)) {
		if(!TranslateAccelerator(wnd.getWindow(), hAccel, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

VOID edgeDetectingThread (PVOID pvoid) {
	 while (runningThread) {
		 if (!pause) detector.update();
	 }
	 _endthread();
}


/**
 * Оконная процедура.
 */
LRESULT CALLBACK mainWindowProcedure(HWND hWnd, UINT message, UINT wParam, LONG lParam) {
	switch(message)	{

	case WM_CREATE:
		runningThread = true;
		setPause(hWnd, false);
		setOperatorType(hWnd, ID_OP_ROBERTS);
		setEffectTypes(hWnd);
		_beginthread(edgeDetectingThread, 0, NULL) ;
		break;
		
	case WM_COMMAND:
		menuCommandSelected(hWnd, wParam);
		break;

	case WM_DESTROY:
		runningThread = false;
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

/**
 * Обработка сообщений диалогового окна "О программе"
 */
BOOL CALLBACK AboutDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch(message) {

	case WM_COMMAND:
		switch(LOWORD(wParam)) {
		case IDC_GO_TO_GIT:
			ShellExecuteA(GetParent(hDlg), "open", "https://github.com/aNNiMON/DonNUEdgeDetector", NULL, NULL, SW_MAXIMIZE);
			return TRUE;
		case IDC_OK:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

/**
 * Обработка события выбранного пункта меню.
 */
void menuCommandSelected(HWND hWnd, UINT wParam) {
	UINT command = LOWORD(wParam);
	switch(command) {

	case ID_SNAPSHOT:
		detector.snapshot();
		break;

	case ID_PAUSE:
		setPause(hWnd, !pause);
		break;

	case ID_OP_ROBERTS:
	case ID_OP_PREWITT:
	case ID_OP_SOBEL:
		setOperatorType(hWnd, command);
		break;

	case ID_EF_ORIGINAL:
	case ID_EF_GRAYSCALE:
	case ID_EF_INVERSE:
		effectsEnabled[EFFECTS_END - command] = !effectsEnabled[EFFECTS_END - command];
		setEffectTypes(hWnd);
		break;

	case ID_ABOUT:
		DialogBox(NULL, MAKEINTRESOURCE(IDD_ABOUT_DIALOG), hWnd, (DLGPROC)AboutDialogProc);
		break;

	case ID_EXIT:
		SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		break;
	}
}

/**
 * Приостановить работу детектора граней.
 */
void setPause(HWND hWnd, bool _pause) {
	pause = _pause;
	HMENU cameraMenu = GetSubMenu(GetMenu(hWnd), 0);
	ULONG check = pause ? MF_CHECKED : MF_UNCHECKED;
	CheckMenuItem(cameraMenu, 1, check);
}

/**
 * Установить тип оператора (ID_OP_ROBERTS, ID_OP_SOBEL, ID_OP_PREWITT);
 */
void setOperatorType(HWND hWnd, UINT type) {
	HMENU viewMenu = GetSubMenu(GetMenu(hWnd), 1);
	CheckMenuRadioItem( viewMenu, OPERATORS_START, OPERATORS_END,
						type, MF_BYCOMMAND );
	detector.setOperator(type);
}

/**
 * Установить тип эффекта (ID_EF_ORIGINAL, ID_EF_GRAYSCALE, ID_EF_INVERSE)
 */
void setEffectTypes(HWND hWnd) {
	HMENU viewMenu = GetSubMenu(GetMenu(hWnd), 1);
	for(int i = EFFECTS_START; i <= EFFECTS_END; i++) {
		int id = EFFECTS_END - i;
		ULONG check = effectsEnabled[id] ? MF_CHECKED : MF_UNCHECKED;
		CheckMenuItem( viewMenu, i, check);
		detector.setEffects(i, effectsEnabled[id]);
	}
}
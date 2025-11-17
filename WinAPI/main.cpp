#include<Windows.h>
#include"resource.h"
#include<commctrl.h>
#include<iostream>

//#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")


CONST WCHAR TEXT_IN_LOGIN[] = L"Введите Логин: ";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//BOOL Edit_SetCueBannerText(HWND hwnd, LPCWSTR lpcwText);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox
	(
		NULL,
		"Hello WinAPI!",
		"MessageBox",
		MB_YESNOCANCEL | MB_ICONASTERISK | MB_HELP
		| MB_SYSTEMMODAL
		| MB_RIGHT
	);*/
	//MB - Message Box
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC) DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG://Выполняется один раз при запуске окна. 
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);
		HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
		setlocale(LC_ALL, "");
		//SetConsoleCP(866);
		SendMessage((hEditLogin), EM_SETCUEBANNER/*(0x1500+1)*/, TRUE, (LPARAM) TEXT_IN_LOGIN);
		//SendMessage((hEditLogin), EM_SETCUEBANNER/*(0x1500+1)*/, TRUE, (LPARAM) L"Введите Логин: ");
		//SetFocus(GetDlgItem(hwnd, IDC_EDIT_LOGIN));
	}
		break;
	case WM_COMMAND:// Обрабатывает команды с клавиатуры и мышки.
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_COPY:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};
			HWND hEditLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);
			HWND hEditPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hEditLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hEditPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
			break;
		case IDOK:
			MessageBox(NULL, "Нажата клавиша ОК", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
		break;
	case WM_CLOSE:// Выполняется при нажатии кнопки 'X'.
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
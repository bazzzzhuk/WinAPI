#include<Windows.h>
#include"resource.h"

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
		break;
	case WM_COMMAND:// Обрабатывает команды с клавиатуры и мышки.
		switch (LOWORD(wParam))
		{
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
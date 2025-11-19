#include<Windows.h>
#include<windowsx.h>
#include<cstdio>
#include<wchar.h>
#include"resource.h"
#include <sstream>
using namespace std;

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "Combo", "Box" };//Use Multi-Byte Character Set
//CONST WCHAR* g_sz_VALUES[] = {L"This", L"is", L"my", L"first", L"Combo", L"Box"};//Use Unicode Character Set

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0;
}
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
	}
	break;
	case WM_COMMAND:
	{
		//CONST CHAR TEXT_IN_LOGIN[] = { "Введите Логин: " + select_key };
		switch (LOWORD(wParam))
		{

		case IDOK:
		{
			//CONST WCHAR TEXT_IN_OK[] = L"Вы выбрали";
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			CONST INT SIZE = 256;
			CHAR buf[SIZE] = {};
			INT select_key = ComboBox_GetCurSel(hCombo);
			//INT select_key = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			SendMessage(hCombo, CB_GETLBTEXT, select_key, (LPARAM)buf);
#ifdef _UNICODE
			wostringstream oss;
#else
			ostringstream oss;
#endif
			oss << select_key;
			if(select_key != CB_ERR){
				CHAR End_Message[SIZE] = {};
				wsprintf(End_Message, "Вы выбрали элемент № %i со значением '%s'", select_key, buf);
				MessageBox(hwnd, End_Message, "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(NULL, "Вы ничего не выбрали!", "Info", MB_OK | MB_ICONERROR);
			}
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
			break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}
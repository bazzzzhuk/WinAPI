#include<Windows.h>
#include"resource.h"

#include<commctrl.h>
#include<iostream>
#include<windowsx.h>
#include<cstdio>
#include<wchar.h>

HINSTANCE hInstance;

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "List","Box" };//Use Multi-Byte Character Set

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgNewElement(HWND hwnd2, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
		HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
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
			HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
			CONST INT SIZE = 256;
			CHAR buf[SIZE] = {};
			INT select_key = ListBox_GetCurSel(hCombo);
			SendMessage(hCombo, LB_GETTEXT, select_key, (LPARAM)buf);
			if (select_key != LB_ERR)
			{
				CHAR End_Message[SIZE] = {};
				wsprintf(End_Message, "Вы выбрали элемент № %i со значением '%s'", select_key + 1, buf);
				MessageBox(hwnd, End_Message, "Info", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, "Вы ничего не выбрали!", "Info", MB_OK | MB_ICONERROR);
			}
			break;
		}
		case IDC_BUTTON1:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwnd, (DLGPROC)DlgNewElement, 0);
			break;
		}
		case IDC_BUTTON2:
		{
			CONST INT SIZE = 256;
			CHAR buf[SIZE] = {};
			HWND hCombo = GetDlgItem(hwnd, IDC_LIST1);
			INT select_key = ListBox_GetCurSel(hCombo);
			if (select_key != LB_ERR)
			{
				SendMessage(hCombo, LB_GETTEXT, select_key, (LPARAM)buf);
				SendMessage(hCombo, LB_DELETESTRING, select_key, 0);
				CHAR End_Message[SIZE] = {};
				wsprintf(End_Message, "Элемент %i со значением '%s' удалён удачно!", select_key + 1, buf, MB_OK | MB_ICONINFORMATION);
				MessageBox(hwnd, End_Message, "Информация", MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, "Вы ничего не выбрали!", "Информация", MB_OK | MB_ICONERROR);
			}
			break;
		}

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
BOOL CALLBACK DlgNewElement(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SetFocus(GetDlgItem(hwnd, IDC_EDIT2));
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			HWND hEditList = GetDlgItem(GetParent(hwnd), IDC_LIST1);
			HWND hCombo2 = GetDlgItem(hwnd, IDC_EDIT2);
			CONST INT SIZE = 256;
			CHAR buf[SIZE] = {};
			SendMessage(hCombo2, WM_GETTEXT, SIZE, (LPARAM)buf);
			MessageBox(hwnd, (LPCSTR)buf, "Информация", MB_OK | MB_ICONINFORMATION);
			SendMessage(hEditList, LB_ADDSTRING, 0, (LPARAM)buf);
		}
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}

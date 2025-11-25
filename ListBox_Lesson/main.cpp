#include<Windows.h>
#include<Windowsx.h>
#include"resource.h"
#include<WinUser.h>
#include<wchar.h>
#include<cstdio>

#include <wincodec.h>
#include <magnification.h>

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "first", "List","Box" };//Use Multi-Byte Character Set


BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcADD(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEDIT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, DlgProc, 0);
	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
		}
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_LIST1:
		{
			switch (HIWORD(wParam))
			{
			case LBN_DBLCLK:
			{
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEDIT, 0);
			}
			break;
			case WM_VKEYTOITEM:
			{
				switch (LOWORD(wParam))
				{
				case 0x20:
				{
					SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_LIST1, LBN_DBLCLK), (LPARAM)GetDlgItem(hwnd, IDC_LIST1));
					break;
				}
				}
				break;
			}
			default: break;
			}
			break;
		}
		case IDC_BUTTON_ADD:
		{
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC)DlgProcADD, 0);
		}
		break;
		case IDC_BUTTON_DELETE:
		{
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
		}
		break;
		case IDC_BUTTON_UP:
		{
			CHAR sz_buffer[256] = {};
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
				INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR)
			{
				INT ii = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
				SendMessage(hListBox, LB_INSERTSTRING, i - 1, (LPARAM)sz_buffer);
				if (i - 1 < 0)i = ii;
				SendMessage(hListBox, LB_SETCURSEL, i - 1, 0);
			}
				break;
		}
		case IDC_BUTTON_DOWN:
		{
			CHAR sz_buffer[256] = {};
			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			if (i != LB_ERR)
			{
				INT ii = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
				if (i + 1 >= ii)i = -1;
				i++;
				SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
				SendMessage(hListBox, LB_SETCURSEL, i, 0);
			}
			break;
		}
		break;
		case IDOK:
			break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
		break;
	}
	case WM_VKEYTOITEM:
	{
		switch (LOWORD(wParam))
		{
		case VK_SPACE:
		{
			MessageBox(hwnd, "Enter pressed", "Info", MB_OK | MB_ICONINFORMATION);
			HWND hList = GetDlgItem(hwnd, IDC_LIST1);
			if (GetFocus() == hList)
			{
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEDIT, 0);
			}
		}
		break;
		}
	}

	//case WM_VKEYTOITEM:
	//{
	//	switch (LOWORD(wParam))
	//		//switch (wParam)
	//	{
	//		//HWND hListBox = GetDlgItem(GetParent(hwnd), IDC_LIST1);
	//		//INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
	//		//SendMessage(hListBox, LB_SETCURSEL, i, 0);
	//		////SetFocus(hListBox);
	//	//if(wParam == VK_SPACE)
	//	case 0x20:
	//	{
	//		SendMessage(hwnd, WM_COMMAND, MAKEWPARAM(IDC_LIST1, LBN_DBLCLK), (LPARAM)GetDlgItem(hwnd, IDC_LIST1));
	//		//SendMessage(hListBox, LB_SETCURSEL, i, 0);
	//		//DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, DlgProcEDIT, 0);
	//	}
	//	}
	//	break;
	//}

	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	}

	return FALSE;
}
BOOL CALLBACK DlgProcADD(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
		SetFocus(hEdit);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_BUFFER[SIZE]{};
			HWND hEdit = GetDlgItem(hwnd, IDC_EDIT);
			SendMessage(hEdit, WM_GETTEXT, SIZE, (LPARAM)sz_BUFFER);
			HWND hParent = GetParent(hwnd);
			HWND hList = GetDlgItem(hParent, IDC_LIST1);
			if (SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_BUFFER) == LB_ERR)
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)sz_BUFFER);
			else
			{
				MessageBox(hwnd, "Такой элемент уже существует", "Warning", MB_OK | MB_ICONWARNING);
				break;
			}
		}

		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
BOOL CALLBACK DlgProcEDIT(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменение элемента");
		CHAR sz_buffer[256] = {};
		HWND hListBox = GetDlgItem(GetParent(hwnd), IDC_LIST1);
		HWND hEditItem = GetDlgItem(hwnd, IDC_EDIT);
		INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
		SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hEditItem, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CHAR sz_buffer[256] = {};
			HWND hListBox = GetDlgItem(GetParent(hwnd), IDC_LIST1);
			HWND hEditItem = GetDlgItem(hwnd, IDC_EDIT);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hEditItem, WM_GETTEXT, 256, (LPARAM)sz_buffer);
			if (SendMessage(hListBox, LB_FINDSTRINGEXACT, 0, (LPARAM)sz_buffer) == LB_ERR)
			{
				SendMessage(hListBox, LB_DELETESTRING, i, 0);
				SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
			}
			else
			{
				MessageBox(hwnd, "Такой элемент уже существует", "Warning", MB_OK | MB_ICONWARNING);
				break;
			}
			EndDialog(hwnd, 0);
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}

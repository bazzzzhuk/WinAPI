//MainWindow
#include<Windows.h>
#include"resource.h"

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";
INT Width_Window = (GetSystemMetrics(SM_CXSCREEN)*0.75);
INT Height_Window = (GetSystemMetrics(SM_CYSCREEN)*0.75);

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	//  Инициализируем размеры и стиль
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);//cb - count bytes
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;
	//  Инициализируем внешний вид окон
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_DOGE));
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_VEGAN));
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "Doge.ico", IMAGE_ICON, LR_DEFAULTSIZE,  LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIcon = (HICON)LoadImage(hInstance, "vegan.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hCursor = (HCURSOR)LoadImage
	(hInstance, 
		"starcraft-original\\c_f_4.cur",
		IMAGE_CURSOR,
		40,
		40,
		LR_LOADFROMFILE
		);
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//  инициализация системных переменных:
	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;
	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//Этап 2 Создание окна 
	HWND hwnd = CreateWindowEx
	(
		NULL,//exStyle
		g_sz_WINDOW_CLASS,//Имя класса окна
		g_sz_WINDOW_CLASS,//Заголовок окна
		WS_OVERLAPPEDWINDOW,//Стиль окна. Стили всегда зависят от класса окна. WS_OVERLAPPEDWINDOW - главное окно.
		(GetSystemMetrics(SM_CXSCREEN) - Width_Window)/2,
		(GetSystemMetrics(SM_CYSCREEN)-Height_Window)/2,
		//Position
		Width_Window, Height_Window,//size window
		NULL,
		NULL,//Для главного окна это ResourceID главного меню, для дочернего окна (Control) ResourceID дочернего окна (IDC_BUTTON_COPY)
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);//Режим отображения окна - (развернут на весь экран, свёрнуто в окно или же свёрнуто на панель задач)
	UpdateWindow(hwnd);//Обновляет рабочую область окна отправляя сообщение WM_Paint, если клиентская область окна не пустая.

	//3. Запуск цикла сообщений.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)>0)
	{
		TranslateMessage(&msg);//Преобразует сообщения виртуальных клавиш в символьные сообщени. 
		DispatchMessage(&msg); //Отправление сообщение в процедуру окна.
	}

	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;
}
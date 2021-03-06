// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT kierunek_x, kierunek_y;
const int MAX_MASS = 40;
struct element
{
	int masa;
	INT obiekt_x;
	INT obiekt_y;
	bool podniesiony;
};
int n = 3;
element towary[3] = { {12, 150, 400, false}, 
{50, 50, 400, false}, {34, 250, 300, false} };

RECT drawArea = { 0, 0, 600, 800};
HWND hwndButton;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
int					mozna_podniesc(element[], int);
int					czy_podniesiony(element[], int);

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255,0,0,255));
	Pen pen2(Color(255, 0, 0, 0));

	graphics.DrawLine(&pen, kierunek_x, 0, kierunek_x, kierunek_y);										// lina
	for (int i = 0; i < n; i++)
	graphics.DrawRectangle(&pen2, towary[i].obiekt_x, towary[i].obiekt_y, 50, 50);						// element
	graphics.DrawLine(&pen, 0, 450, 600, 450);															// podloga
	graphics.DrawLine(&pen, 600, 0, 600, 450);															// sciana
}


int OnCreate(HWND window)
{
   SetTimer(window, TMR_1, 25, 0);
   return 0;
}



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	kierunek_x = 100;
	kierunek_y = 300;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   
   hwndButton = CreateWindow(TEXT("button"), TEXT("góra"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   1000, 0, 50, 50, hWnd, (HMENU)ID_BUTTON1, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("dó3"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   1000, 100, 50, 50, hWnd, (HMENU)ID_BUTTON2, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("lewo"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   950, 50, 50, 50, hWnd, (HMENU)ID_BUTTON3, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("prawo"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   1050, 50, 50, 50, hWnd, (HMENU)ID_BUTTON4, hInstance, NULL);

   hwndButton = CreateWindow(TEXT("button"), TEXT("podnies"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   975, 200, 100, 50, hWnd, (HMENU)ID_BUTTON5, hInstance, NULL);
	
	hwndButton = CreateWindow(TEXT("button"), TEXT("upusc"),
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   975, 300, 100, 50, hWnd, (HMENU)ID_BUTTON6, hInstance, NULL);
   OnCreate(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

	if (mozna_podniesc(towary, n))
	{
		EnableWindow(GetDlgItem(hWnd, ID_BUTTON5), TRUE);
	}
	else
		EnableWindow(GetDlgItem(hWnd, ID_BUTTON5), FALSE);
	if (czy_podniesiony(towary, n) )
	{
		EnableWindow(GetDlgItem(hWnd, ID_BUTTON6), TRUE);
	}
	else
		EnableWindow(GetDlgItem(hWnd, ID_BUTTON6), FALSE);
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			kierunek_y -= 10;
			if (czy_podniesiony(towary, n))
				towary[czy_podniesiony(towary, n) - 1].obiekt_y -= 10;
			break;
		case ID_BUTTON2:
			if (czy_podniesiony(towary, n) ){						
			if (towary[czy_podniesiony(towary, n) - 1].obiekt_y < 400){
				kierunek_y += 10;
				towary[czy_podniesiony(towary, n) - 1].obiekt_y += 10; } }
			else if ( !czy_podniesiony(towary, n) && kierunek_y < 450)
				kierunek_y += 10;
			break;
		case ID_BUTTON3:
			kierunek_x -= 10;
			if (czy_podniesiony(towary, n))
				towary[czy_podniesiony(towary, n) - 1].obiekt_x -= 10;
			break;
		case ID_BUTTON4:
			if (czy_podniesiony(towary, n) ){				
			if(towary[czy_podniesiony(towary, n) - 1].obiekt_x < 550){
				kierunek_x += 10;
				towary[czy_podniesiony(towary, n) - 1].obiekt_x += 10; } }
			else if (kierunek_y < 600)
				kierunek_x += 10;
			break;
		case ID_BUTTON5:
			if(mozna_podniesc(towary, n))
			towary[mozna_podniesc(towary, n) - 1].podniesiony = true;
			break;
		case ID_BUTTON6:
			if(czy_podniesiony(towary, n))
			towary[czy_podniesiony(towary, n) - 1].podniesiony = false;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
			case TMR_1:
				//force window to repaint
				for (int i = 0; i < n; i++){
				if (towary[i].podniesiony == false && towary[i].obiekt_y < 400)
				towary[i].obiekt_y += 10; }
				InvalidateRect(hWnd, &drawArea, TRUE);
				hdc = BeginPaint(hWnd, &ps);
				MyOnPaint(hdc);
				EndPaint(hWnd, &ps);
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

int mozna_podniesc(element towary[], int n)																//	sprawdza czy mozna zaczepic dzwig o obiekt i zwraca jego numer
{
	for (int i = 0; i < n; i++)
	if ( (kierunek_x >= towary[i].obiekt_x) && (kierunek_x <= towary[i].obiekt_x+50) && (kierunek_y == towary[i].obiekt_y) && (towary[i].podniesiony == false) && (towary[i].masa <= MAX_MASS))
	return (i + 1);
	return 0;
}

int czy_podniesiony(element towary[], int n)															//	sprawdza czy jakis obiekt jest zaczepiony i zwraca jego numer
{
	for (int i = 0; i < n; i++)
	if (towary[i].podniesiony == true)
	return i + 1;
	return 0;
}

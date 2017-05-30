// FineChess.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "FineChess.h"

#include "allvalue.h"
#include "chess.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

Chess cChess;

#include "platform.h"

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FINECHESS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_FINECHESS);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

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

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_FINECHESS);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)CreateSolidBrush( RGB(255,255,0));
	wcex.lpszMenuName	= (LPCTSTR)IDC_FINECHESS;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
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

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
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

	switch (message) 
	{
	case WM_CREATE:
		cChess.reChess();
		hdc=GetDC(hWnd);
		ReleaseDC(hWnd,hdc);
		flag = true;
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_FILE_RESTART:
			cChess.reChess();
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		case ID_FILE_BACK:
			cChess.StepBack();
			InvalidateRect(hWnd,&rcPre,TRUE);
			InvalidateRect(hWnd,&rc,TRUE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case  WM_KEYDOWN:
		{
			if( wParam==VK_LEFT || wParam=='a' || wParam=='A' )
				cChess.Left();
			else if( wParam==VK_RIGHT || wParam=='d' || wParam=='D' )
				cChess.Right();
			else if( wParam==VK_UP || wParam=='w' || wParam=='W' )
				cChess.Up();
			else if( wParam==VK_DOWN || wParam=='s' || wParam=='S' )
				cChess.Down();
			else if( wParam==VK_RETURN || wParam==VK_TAB || wParam==' ' ){
				int iWin=cChess.PutKey();
				if( iWin==1 ){
					MessageBox(hWnd,TEXT("Player 1 is winer!"),TEXT("WIN"),NULL);
					cChess.reChess();
				}
				else if( iWin==2 ){
					MessageBox(hWnd,TEXT("Player 2 is winer!"),TEXT("WIN"),NULL);
					cChess.reChess();
				}
				InvalidateRect(hWnd,NULL,TRUE);
			}
			InvalidateRect(hWnd,&rcPre,TRUE);
			InvalidateRect(hWnd,&rc,TRUE);	
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetBkColor(hdc,RGB(255,255,0));
		SetBkMode(hdc,2);
		fnDrawChess();
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		cxClient=LOWORD(lParam);
		cyClient=HIWORD(lParam);
		flag = true;
		break;
	case WM_LBUTTONDOWN:
		{
			int iWin=cChess.MouseDown( LOWORD(lParam),HIWORD(lParam) );
			if( iWin==3 ){
				InvalidateRect(hWnd,&rcPre,TRUE);
				InvalidateRect(hWnd,&rc,TRUE);
			}
			else if( iWin==1 ){
				InvalidateRect(hWnd,&rcPre,TRUE);
				InvalidateRect(hWnd,&rc,TRUE);
				MessageBox(hWnd,TEXT("Player 1 is winner!"),TEXT("Win"),NULL);
				cChess.reChess();
				InvalidateRect(hWnd,NULL,TRUE);
			}
			else if( iWin==2 ){
				InvalidateRect(hWnd,&rcPre,TRUE);
				InvalidateRect(hWnd,&rc,TRUE);
				MessageBox(hWnd,TEXT("Player 2 is winner!"),TEXT("Win"),NULL);
				cChess.reChess();
				InvalidateRect(hWnd,NULL,TRUE);
			}
		}
		break;
	case WM_MOUSEMOVE:
		if( cChess.MouseMove( LOWORD(lParam),HIWORD(lParam) ) ){
			InvalidateRect(hWnd,&rcPre,TRUE);
			InvalidateRect(hWnd,&rc,TRUE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;	
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}



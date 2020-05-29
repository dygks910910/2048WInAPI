#include <windows.h>
#include"resource.h"
#include"GameManager.h"
#include"define.h"
//#include<crtdbg.h>
#include"CYHTime.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass = "2048";
HDC hdc,memdc,mem2dc;
PAINTSTRUCT ps;
HBITMAP oldbmp,oldbmp2,hbmp,hbmpBack;
CGameManager* gameManager; 
e_BITMAP_TYPE destScore = e_BITMAP_TYPE::TYPE11;
bool bDone = false;
CYHTime g_timer;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{

	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	gameManager = new CGameManager(g_hInst);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		0, 0, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH, name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);


	/*while (GetMessage(&Message,hWnd, 0, 0))	{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
	}*/

	bool bDone = false;
	while (!bDone)
	{
		g_timer.StartTimer();
		if(PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)

			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
		{
			gameManager->update();
		}
		InvalidateRect(hWnd, NULL, false);
		UpdateWindow(hWnd);
		g_timer.EndTimer();
	}
	return Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int answear = 0;
	switch (iMessage) {
	case WM_CREATE:
		//gameManager = new CGameManager(g_hInst);
		hbmpBack = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP12));
		//SetTimer(hWnd, 1, 0, nullptr);
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		gameManager->setMouseDirection(iMessage, LOWORD(lParam), HIWORD(lParam));
		//if (iMessage == WM_LBUTTONUP)
		//InvalidateRect(hWnd, nullptr, true);
		if (destScore == gameManager->getHighType())
		{
			MessageBox(hWnd, "목표달성", "목표달성!종료합니다.", MB_OK);
			PostQuitMessage(0);
		}
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_GAME_NEWGAME:
			delete gameManager;
			gameManager = new CGameManager(g_hInst);
			break;
		case ID_GAME_EXIT:
			answear = MessageBox(hWnd, "종료하시겠습니까?", "종료", MB_OKCANCEL);
			if (answear == IDOK)
			{
				delete gameManager;
				PostQuitMessage(0);
			}
			break;
		case ID_DESTINATION_256:
			destScore = e_BITMAP_TYPE::TYPE8;
			break;
		case ID_DESTINATION_512:
			destScore = e_BITMAP_TYPE::TYPE9;
			break;
		case ID_DESTINATION_1024:
			destScore = e_BITMAP_TYPE::TYPE10;
			break;
		case ID_DESTINATION_2048:
			destScore = e_BITMAP_TYPE::TYPE11;
			break;
		}
	case WM_TIMER:
		/*gameManager->timer();
		InvalidateRect(hWnd, nullptr, false);*/
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (hbmp == NULL)
		{
			hbmp = CreateCompatibleBitmap(hdc, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH, name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT);
		}
		memdc = CreateCompatibleDC(hdc);
		mem2dc = CreateCompatibleDC(memdc);

		oldbmp = (HBITMAP)SelectObject(memdc, hbmp);
		oldbmp2 = (HBITMAP)SelectObject(mem2dc, hbmpBack);
		
		
		StretchBlt(memdc, 0, 0, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH, name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT, mem2dc, 0, 0, 320, 479, SRCCOPY);
		gameManager->render(memdc);
		
		
		BitBlt(hdc, 0, 0, 600, 600, memdc, 0, 0, SRCCOPY);
		
		
		SelectObject(mem2dc, oldbmp2);
		DeleteDC(mem2dc);
		SelectObject(memdc, oldbmp);
		DeleteDC(memdc);
		
		EndPaint(hWnd, &ps);
		gameManager->FindHighType();
		

		break;
	case WM_DESTROY:
		delete gameManager;
		//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
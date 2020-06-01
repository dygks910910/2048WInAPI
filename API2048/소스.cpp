#include <windows.h>
#include"resource.h"
#include"GameManager.h"
#include"define.h"
#include<crtdbg.h>
#include"CYHTime.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPSTR lpszClass = "2048";
HDC g_hdc;
CGameManager* g_pGameManager; 
e_BITMAP_TYPE destScore = e_BITMAP_TYPE::TYPE11;
bool bDone = false;
CYHTime* g_pTimer;
double g_dElapsedTime = 0;
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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		0, 0, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH, name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);


	/*while (GetMessage(&Message,hWnd, 0, 0))
	{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
	}*/

	g_pTimer = new CYHTime;
	bool bDone = false;
	g_hdc = GetDC(hWnd);
	g_pGameManager = new CGameManager();

	while (!bDone)
	{
		g_pTimer->StartTimer();
		if(PeekMessage(&Message, 0, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)

			{
				bDone = true;
				SAFE_DELETE(g_pGameManager);
				SAFE_DELETE(g_pTimer);
				break;

			}
			else
			{
				TranslateMessage(&Message);
				DispatchMessage(&Message);
			}
		}
		else
		{
			g_pGameManager->update();
			g_pGameManager->render(g_hdc);
		}
		InvalidateRect(hWnd, NULL, false);
		UpdateWindow(hWnd);
		g_pTimer->EndTimer();
		g_dElapsedTime += g_pTimer->GetDeltaTime();
	}
	//return Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int answear = 0;
	switch (iMessage) {
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		g_pGameManager->setMouseDirection(iMessage, LOWORD(lParam), HIWORD(lParam));
		//if (iMessage == WM_LBUTTONUP)
		//InvalidateRect(hWnd, nullptr, true);
		if (destScore == g_pGameManager->getHighType())
		{
			MessageBox(hWnd, "목표달성", "목표달성!종료합니다.", MB_OK);
			PostQuitMessage(0);
		}
		break;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_GAME_NEWGAME:
			SAFE_DELETE(g_pGameManager);
			g_pGameManager = new CGameManager();
			break;
		case ID_GAME_EXIT:
			answear = MessageBox(hWnd, "종료하시겠습니까?", "종료", MB_OKCANCEL);
			if (answear == IDOK)
				PostQuitMessage(0);
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
	case WM_DESTROY:
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		PostQuitMessage(0);
		//SendMessage(hWnd, WM_QUIT, 0, 0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
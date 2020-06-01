#include "GameManager.h"
#include<chrono>
#include<iostream>
#include"resource.h"
CGameManager::CGameManager()
{
	srand(time(NULL));
	m_pBoard = new CNewBoard;
	m_pMouse = new CMouse;
	m_iHighType = e_BITMAP_TYPE::TYPE1;
	m_hbmpBack = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP13));
	m_hbmp = CreateCompatibleBitmap(g_hdc, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH, name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT);
	m_memBackdc = CreateCompatibleDC(g_hdc);
	m_BackgroundDC = CreateCompatibleDC(m_memBackdc);
}


CGameManager::~CGameManager()
{
	SAFE_DELETE(m_pMouse);
	SAFE_DELETE(m_pBoard);

	SelectObject(m_BackgroundDC, m_oldbmp2);
	DeleteDC(m_BackgroundDC);
	SelectObject(m_memBackdc, m_oldbmp);
	DeleteDC(m_memBackdc);
	DeleteDC(g_hdc);
}

void CGameManager::render(HDC hdc)
{
	

	m_oldbmp = (HBITMAP)SelectObject(m_memBackdc, m_hbmp);
	m_oldbmp2 = (HBITMAP)SelectObject(m_BackgroundDC, m_hbmpBack);

	StretchBlt(m_memBackdc, 0, 0, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH, name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT, m_BackgroundDC, 0, 0, 237, 167, SRCCOPY);

	m_pBoard->Render(m_memBackdc);
	char cTime[20];
	itoa(g_dElapsedTime, cTime, 10);
	TextOut(m_memBackdc, 0, 20, cTime, strlen(cTime));
	if (m_pMouse->getDirection() == e_DIRECTION::RIGHT)
		TextOut(m_memBackdc, 0, 0, "RIGHT", strlen("RIGHT"));
	if (m_pMouse->getDirection() == e_DIRECTION::LEFT)
		TextOut(m_memBackdc, 0, 0, "LEFT", strlen("LEFT"));
	if (m_pMouse->getDirection() == e_DIRECTION::UP)
		TextOut(m_memBackdc, 0, 0, "UP", strlen("UP"));
	if (m_pMouse->getDirection() == e_DIRECTION::DOWN)
		TextOut(m_memBackdc, 0, 0, "DOWN", strlen("DOWN"));
	if (m_pMouse->getDirection() == e_DIRECTION::STOP)
		TextOut(m_memBackdc, 0, 0, "STOP", strlen("STOP"));

	BitBlt(hdc, 0, 0, 600, 600, m_memBackdc, 0, 0, SRCCOPY);


	
}


void CGameManager::setMouseDirection(UINT msg, const int &mx, const int &my)//방향세팅.
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		m_pMouse->setStartX(mx);
		m_pMouse->setStartY(my);
		break;
	case WM_LBUTTONUP:
		if (m_pMouse->getDirection() == e_DIRECTION::STOP)
		{
			m_pMouse->setEndX(mx);
			m_pMouse->setEndY(my);
			m_pMouse->setDirection(name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH);
			//m_pBoard->ChangedMouseState(e_Event::BMP_LEVELUP);
			m_pBoard->CalcBlockMove(m_pMouse->getDirection());
			m_pBoard->ChangedMouseState(e_Event::BLOCK_MOVE);
		}
		break;
	}
}





void CGameManager::update()
{
	m_pBoard->Update(m_pMouse->getDirection());
	if (m_pMouse->getDirection() != e_DIRECTION::STOP)
	{
		if (m_pBoard->CheckAllBlockStop())
		{
			m_pBoard->MakeBlock();
			m_pMouse->setDIrec(e_DIRECTION::STOP);
		}
	}
}

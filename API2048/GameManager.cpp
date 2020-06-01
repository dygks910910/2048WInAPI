#include "GameManager.h"
#include<chrono>
#include<iostream>
CGameManager::CGameManager()
{
	srand(time(NULL));
	m_pBoard = new CNewBoard;
	m_pMouse = new CMouse;
	m_iHighType = e_BITMAP_TYPE::TYPE1;

}


CGameManager::~CGameManager()
{
	SAFE_DELETE(m_pMouse);
	SAFE_DELETE(m_pBoard);
}

void CGameManager::render(HDC hdc)
{
	m_pBoard->Render(hdc);
	char cTime[20];
	itoa(g_dElapsedTime,cTime, 10);
	TextOut(hdc, 0, 20, cTime, strlen(cTime));
	if (m_pMouse->getDirection() == e_DIRECTION::RIGHT)
		TextOut(hdc, 0, 0, "RIGHT", strlen("RIGHT"));
	if (m_pMouse->getDirection() == e_DIRECTION::LEFT)
		TextOut(hdc, 0, 0, "LEFT", strlen("LEFT"));
	if (m_pMouse->getDirection() == e_DIRECTION::UP)
		TextOut(hdc, 0, 0, "UP", strlen("UP"));
	if (m_pMouse->getDirection() == e_DIRECTION::DOWN)
		TextOut(hdc, 0, 0, "DOWN", strlen("DOWN"));
	if (m_pMouse->getDirection() == e_DIRECTION::STOP)
		TextOut(hdc, 0, 0, "STOP", strlen("STOP"));
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

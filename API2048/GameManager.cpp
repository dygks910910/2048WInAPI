#include "GameManager.h"
#include<chrono>
#include<iostream>
CGameManager::CGameManager(HINSTANCE inst) :m_g_hinst(inst)
{
	srand(time(NULL));
	m_pBoard = new CBoard;
	m_pMouse = new CMouse;
	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)
	{
		m_pBlockArr[i] = nullptr;
	}
	makeBlock();
	makeBlock();
	m_iHighType = e_BITMAP_TYPE::TYPE1;

}


CGameManager::~CGameManager()
{
	delete m_pMouse;
	delete m_pBoard;
	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)
	{
		if (!checkNull(m_pBlockArr[i]))
			delete m_pBlockArr[i];
	}
}

void CGameManager::render(HDC hdc)
{
	m_pBoard->render(hdc);
	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)
	{
		if (!checkNull(m_pBlockArr[i]))
			m_pBlockArr[i]->render(hdc);
	}
		
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

void CGameManager::progress()
{
	/*if (m_pMouse->getDirection() == e_DIRECTION::STOP)
		return;
	checkInBoardBlock();*/
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
		m_pMouse->setEndX(mx);
		m_pMouse->setEndY(my);
		m_pMouse->setDirection(name_CLIENT_SIZE::CLIENT_SIZE_HEIGHT, name_CLIENT_SIZE::CLIENT_SIZE_WIDTH/*m_pBoard->getRectangleArr()[3][3]->getPosition().x,
			m_pBoard->getRectangleArr()[3][3]->getPosition().y*/);
		
		progress();
		break;
	}
}

void CGameManager::makeBlock()
{
	/*int x, y = 0;
	bool check = true;
	if (m_iBlockNum > 16)
	{
		check = false;
	}
	while (check)
	{
		x = rand() % 4;
		y = rand() % 4;
		if (!(m_pBoard->getRectangleArr()[y][x]->getCheckBlock()))
		{
			for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)
			{
				if (m_pBlockArr[i] == nullptr)
				{
					m_pBlockArr[i] = new CBlock(m_pBoard->getRectangleArr()[y][x]->getPosition(), m_g_hinst);
					m_iBlockNum++;
					check = false;
					break;
				}

			}
		}
	}*/

}

void CGameManager::checkInBoardBlock()
{
	bool check = true;
	int iBlockIndex = 0;
	for (int i = 0; i < name_BOARD_ARR_INFO::BOARD_INDEX_Y; i++)
	{
		for (int j = 0; j < name_BOARD_ARR_INFO::BOARD_INDEX_X; j++)
		{
			while (check)
			{
				if (!checkNull(m_pBlockArr[iBlockIndex]))
					if (m_pBoard->getRectangleArr()[i][j]->getPosition().x == m_pBlockArr[iBlockIndex]->getPosition().x
						&&m_pBoard->getRectangleArr()[i][j]->getPosition().y == m_pBlockArr[iBlockIndex]->getPosition().y)
					{
						m_pBoard->getRectangleArr()[i][j]->setCheckBlock(true);
						m_pBoard->getRectangleArr()[i][j]->setBlockAddr(m_pBlockArr[iBlockIndex]);
						m_pBlockArr[iBlockIndex]->setIndexInfo(j, i);
						check = false;
						break;
					}
					else if (m_pBoard->getRectangleArr()[i][j]->getPosition().x != m_pBlockArr[iBlockIndex]->getPosition().x
						&&m_pBoard->getRectangleArr()[i][j]->getPosition().y != m_pBlockArr[iBlockIndex]->getPosition().y)
					{
						m_pBoard->getRectangleArr()[i][j]->setCheckBlock(false);
						m_pBoard->getRectangleArr()[i][j]->setBlockAddr(m_pBlockArr[iBlockIndex]);


					}
				if (iBlockIndex == name_BLOCK_INFO::MAX_BLOCK_NUM - 1)
				{
					check = false;
				}
				iBlockIndex++;
			}
			check = true;
			iBlockIndex = 0;

		}
	}
	m_pBoard->getRectangleArr();
}



void CGameManager::sortFunc(const int &direction)
{
	//CBlock* temp = nullptr;
	//switch (direction)
	//{
	//case e_DIRECTION::LEFT:
	//	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)//x작은게 앞로감.
	//	{
	//		for (int j = 0; j < name_BLOCK_INFO::MAX_BLOCK_NUM - 1; j++)
	//		{
	//			if (!checkNull(m_pBlockArr[j + 1]) && m_pBlockArr[j] != nullptr)
	//				if (m_pBlockArr[j]->getPosition().x > m_pBlockArr[j + 1]->getPosition().x)
	//				{
	//					temp = m_pBlockArr[j];
	//					m_pBlockArr[j] = m_pBlockArr[j + 1];
	//					m_pBlockArr[j + 1] = temp;
	//					temp;
	//				}
	//		}
	//	}
	//	break;
	//case e_DIRECTION::RIGHT:
	//	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)//x큰게 앞로감.
	//	{
	//		for (int j = 0; j < name_BLOCK_INFO::MAX_BLOCK_NUM - 1; j++)
	//		{
	//			if (!checkNull(m_pBlockArr[j + 1]) && m_pBlockArr[j] != nullptr)
	//				if (m_pBlockArr[j]->getPosition().x < m_pBlockArr[j + 1]->getPosition().x)
	//				{
	//					temp = m_pBlockArr[j + 1];
	//					m_pBlockArr[j + 1] = m_pBlockArr[j];
	//					m_pBlockArr[j] = temp;
	//					temp;
	//				}
	//		}
	//	}
	//	break;
	//case e_DIRECTION::DOWN:
	//	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)//x큰게 앞로감.
	//	{
	//		for (int j = 0; j < name_BLOCK_INFO::MAX_BLOCK_NUM - 1; j++)
	//		{
	//			if (!checkNull(m_pBlockArr[j + 1]) && m_pBlockArr[j] != nullptr)
	//				if (m_pBlockArr[j]->getPosition().y < m_pBlockArr[j + 1]->getPosition().y)
	//				{
	//					temp = m_pBlockArr[j + 1];
	//					m_pBlockArr[j + 1] = m_pBlockArr[j];
	//					m_pBlockArr[j] = temp;
	//					temp;
	//				}
	//		}
	//	}
	//	break;
	//case e_DIRECTION::UP:
	//	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)//x작은게 앞로감.
	//	{
	//		for (int j = 0; j < name_BLOCK_INFO::MAX_BLOCK_NUM - 1; j++)
	//		{
	//			if (!checkNull(m_pBlockArr[j + 1]) && m_pBlockArr[j] != nullptr)
	//				if (m_pBlockArr[j]->getPosition().y > m_pBlockArr[j + 1]->getPosition().y)
	//				{
	//					temp = m_pBlockArr[j];
	//					m_pBlockArr[j] = m_pBlockArr[j + 1];
	//					m_pBlockArr[j + 1] = temp;
	//					temp;
	//				}
	//		}
	//	}
	//	break;
	//}
}

void CGameManager::move()
{
	//int y, x = 0;
	//m_bBlockIsMoving = false;
	//for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)
	//{
	//	if (!checkNull(m_pBlockArr[i]))
	//	{
	//		y = m_pBlockArr[i]->getIndexInfo().y;
	//		x = m_pBlockArr[i]->getIndexInfo().x;
	//		switch (m_pMouse->getDirection())
	//		{
	//		case e_DIRECTION::RIGHT:
	//			if (y < name_BOARD_ARR_INFO::BOARD_INDEX_X
	//				&& x < name_BOARD_ARR_INFO::BOARD_INDEX_Y
	//				&& x + 1 != name_BOARD_ARR_INFO::BOARD_INDEX_X
	//				&& m_pBlockArr[i] != nullptr)
	//			{
	//				//블럭이 있는곳 탐색.
	//				int blockPosX = 3;
	//				for (int idx = 1; idx < 4-x; ++idx)
	//				{
	//					if (m_pBoard->getRectangleArr()[y][x + idx]->getCheckBlock())
	//						blockPosX = x + idx;
	//				}
	//				if (!(m_pBoard->getRectangleArr()[y][blockPosX]->getCheckBlock()))//블럭이 없으면
	//				{
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y][blockPosX]->getPosition());
	//					//m_pBlockArr[i]->setIsMoving(true);
	//				}
	//				//블럭이 있고 같은 타입이면?
	//				else if (m_pBoard->getRectangleArr()[y][blockPosX]->getCheckBlock()
	//					&& m_pBoard->getRectangleArr()[y][blockPosX]->getBlockAddr()->getBitmapType() == m_pBlockArr[i]->getBitmapType())
	//				{
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y][blockPosX]->getPosition());
	//					/*delete m_pBlockArr[i];
	//					m_iBlockNum--;
	//					m_pBlockArr[i] = nullptr;
	//					m_pBoard->getRectangleArr()[y][blockPosX]->getBlockAddr()->setBitmapType(m_pBoard->getRectangleArr()[y][blockPosX]->getBlockAddr()->getBitmapType() + 1);*/
	//					break;
	//				}

	//			}
	//			else
	//			{
	//				//m_pBlockArr[i]->setIsMoving(false);
	//			}
	//			m_bBlockIsMoving |= m_pBlockArr[i]->getisMoving();
	//			break;
	//		case e_DIRECTION::LEFT:
	//			if (y >= 0
	//				&& x >= 0
	//				&& x - 1 >= 0
	//				&& m_pBlockArr[i] != nullptr)
	//			{
	//				int blockPosX = 0;
	//				for (int idx = 1; idx >= 0 && idx <= x; ++idx)
	//				{
	//					if (m_pBoard->getRectangleArr()[y][x - idx]->getCheckBlock())
	//						blockPosX = x - idx;
	//				}

	//				if (!(m_pBoard->getRectangleArr()[y][blockPosX]->getCheckBlock()))
	//				{
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y][blockPosX]->getPosition());
	//					//m_pBlockArr[i]->setIsMoving(true);
	//				}
	//				else if (m_pBoard->getRectangleArr()[y][blockPosX]->getCheckBlock() && m_pBoard->getRectangleArr()[y][blockPosX]->getBlockAddr()->getBitmapType() == m_pBlockArr[i]->getBitmapType())
	//				{
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y][blockPosX]->getPosition());
	//					/*delete m_pBlockArr[i];
	//					m_iBlockNum--;
	//					m_pBlockArr[i] = nullptr;
	//					m_pBoard->getRectangleArr()[y][blockPosX]->getBlockAddr()->setBitmapType(m_pBoard->getRectangleArr()[y][blockPosX]->getBlockAddr()->getBitmapType() + 1);*/
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				//m_pBlockArr[i]->setIsMoving(false);
	//			}
	//			m_bBlockIsMoving |= m_pBlockArr[i]->getisMoving();
	//			break;
	//		case e_DIRECTION::DOWN:
	//			if (y < name_BOARD_ARR_INFO::BOARD_INDEX_Y
	//				&& x < name_BOARD_ARR_INFO::BOARD_INDEX_X
	//				&& y + 1 != name_BOARD_ARR_INFO::BOARD_INDEX_Y && m_pBlockArr[i] != nullptr)
	//			{
	//				if (!(m_pBoard->getRectangleArr()[y + 1][x]->getCheckBlock()))
	//				{
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y + 1][x]->getPosition());
	//					//m_pBlockArr[i]->setIsMoving(true);
	//				}
	//				else if (m_pBoard->getRectangleArr()[y + 1][x]->getCheckBlock()
	//					&& m_pBoard->getRectangleArr()[y + 1][x]->getBlockAddr()->getBitmapType() == m_pBlockArr[i]->getBitmapType())
	//				{
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y + 1][x]->getPosition());
	//					delete m_pBlockArr[i];
	//					m_iBlockNum--;
	//					m_pBlockArr[i] = nullptr;
	//					//m_pBoard->getRectangleArr()[y + 1][x]->getBlockAddr()->setBitmapType(m_pBoard->getRectangleArr()[y + 1][x]->getBlockAddr()->getBitmapType() + 1);
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				//m_pBlockArr[i]->setIsMoving(false);
	//			}
	//			m_bBlockIsMoving |= m_pBlockArr[i]->getisMoving();
	//			break;
	//		case e_DIRECTION::UP:
	//			if (y >= 0 && x >= 0 && y - 1 >= 0)
	//			{
	//				if (!(m_pBoard->getRectangleArr()[y - 1][x]->getCheckBlock())
	//					&& m_pBlockArr[i] != nullptr)
	//				{
	//					//m_pBlockArr[i]->setIsMoving(true);
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y - 1][x]->getPosition());
	//				}
	//				else if (m_pBoard->getRectangleArr()[y - 1][x]->getCheckBlock() && m_pBoard->getRectangleArr()[y - 1][x]->getBlockAddr()->getBitmapType() == m_pBlockArr[i]->getBitmapType())
	//				{
	//					m_pBlockArr[i]->move(m_pMouse->getDirection(), m_pBoard->getRectangleArr()[y - 1][x]->getPosition());
	//					delete m_pBlockArr[i];
	//					m_iBlockNum--;
	//					m_pBlockArr[i] = nullptr;
	//					//m_pBoard->getRectangleArr()[y - 1][x]->getBlockAddr()->setBitmapType(m_pBoard->getRectangleArr()[y - 1][x]->getBlockAddr()->getBitmapType() + 1);
	//					break;
	//				}
	//			}
	//			else
	//			{
	//				//m_pBlockArr[i]->setIsMoving(false);
	//			}
	//			m_bBlockIsMoving |= m_pBlockArr[i]->getisMoving();
	//			break;
	//		}
	//	}
	//}
	//if (!m_bBlockIsMoving)
	//{
	//	m_pMouse->setDIrec(e_DIRECTION::STOP);
	//}
}


void CGameManager::update()
{
	/*if (m_pMouse->getDirection() != e_DIRECTION::STOP) {
		m_bBlockIsMoving = true;*/
		switch (m_pMouse->getDirection())
		{
		case e_DIRECTION::RIGHT:
			//sortFunc(e_DIRECTION::RIGHT);
			move();
			break;
		case e_DIRECTION::LEFT:
			//sortFunc(e_DIRECTION::LEFT);
			move();
			break;
		case e_DIRECTION::DOWN:
			//sortFunc(e_DIRECTION::DOWN);
			move();
			break;
		case e_DIRECTION::UP:
			//sortFunc(e_DIRECTION::UP);
			move();
			break;
		case e_DIRECTION::STOP:
			break;
		}
		//checkInBoardBlock();
	/*}
	else
	{
		m_bBlockIsMoving = false;
	}*/


}

void CGameManager::FindHighType()
{
	e_BITMAP_TYPE temp = e_BITMAP_TYPE::TYPE1;
	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; i++)
	{
		if (!checkNull(m_pBlockArr[i]))
		{
			if (temp < m_pBlockArr[i]->getBitmapType())
			{
				temp = m_pBlockArr[i]->getBitmapType();
			}
		}
	}
	m_iHighType = temp;
}

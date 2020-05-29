#include "Board.h"


CBoard::CBoard()
{
	m_bCheckInBoard = false;
	for (int i = 0; i < name_BOARD_ARR_INFO::BOARD_INDEX_Y; i++)
	{
		for (int j = 0; j < name_BOARD_ARR_INFO::BOARD_INDEX_X; j++)
		{
			CVector2 poTemp;
			poTemp.x = j*name_RECT_INFO::RECT_WIDTH + name_RECT_INFO::RECT_WIDTH;
			poTemp.y = i*name_RECT_INFO::RECT_WIDTH + name_RECT_INFO::RECT_WIDTH;
			m_RectangleArr[i][j] = new CRectangle(poTemp);
		}
	}
}


CBoard::~CBoard()
{
	for (int i = 0; i < name_BOARD_ARR_INFO::BOARD_INDEX_Y; i++)
	{
		for (int j = 0; j < name_BOARD_ARR_INFO::BOARD_INDEX_X; j++)
		{
			delete m_RectangleArr[i][j];
		}
	}
}

void CBoard::render(HDC hdc)
{
	for (int i = 0; i < name_BOARD_ARR_INFO::BOARD_INDEX_Y; i++)
	{
		for (int j = 0; j < name_BOARD_ARR_INFO::BOARD_INDEX_X; j++)
		{
			m_RectangleArr[i][j]->render(hdc);
		}
	}
}
#pragma once
#include"Rectangle.h"
class CBoard
{
public:
	CBoard();
	~CBoard();
public:
	void render(HDC hdc);
	//getter
	CRectangle* (*getRectangleArr())[name_BOARD_ARR_INFO::BOARD_INDEX_X]{return m_RectangleArr; }
	bool getCheckInBoard(){ return m_bCheckInBoard; };
	//setter
	void setCheckInBoard(const bool &b){ m_bCheckInBoard = b; }
private:
	CRectangle *m_RectangleArr[name_BOARD_ARR_INFO::BOARD_INDEX_Y][name_BOARD_ARR_INFO::BOARD_INDEX_X];
	bool m_bCheckInBoard;

};


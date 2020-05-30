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
	CRectangle* (*getRectangleArr())[BD_INFO::BOARD_INDEX_X]{return m_RectangleArr; }
	bool getCheckInBoard(){ return m_bCheckInBoard; };
	//setter
	void setCheckInBoard(const bool &b){ m_bCheckInBoard = b; }
private:
	CRectangle *m_RectangleArr[BD_INFO::MAXY][BD_INFO::BOARD_INDEX_X];
	bool m_bCheckInBoard;

};


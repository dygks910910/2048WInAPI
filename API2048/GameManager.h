#pragma once
#include"Mouse.h"
#include"CNewBoard.h"
#include"inline.h"
#include<time.h>
class CGameManager
{

public:
	CGameManager();
	~CGameManager();
public:
	void render(HDC hdc);
	void setMouseDirection(UINT msg, const int &mx, const int &my);//방향세팅.
	void update();
	e_BITMAP_TYPE getHighType(){ return m_iHighType; }
	void setHighType(const e_BITMAP_TYPE&num){ m_iHighType = num; }
	/*bool getBlockMovingState()const { return m_bBlockIsMoving; }
	void setBlockMovingState(bool b) { m_bBlockIsMoving = b; }*/
private:
	CNewBoard* m_pBoard;
	CMouse* m_pMouse;
private:
	e_BITMAP_TYPE m_iHighType;
public:
	

};


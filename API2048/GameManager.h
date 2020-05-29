#pragma once
#include"Board.h"
#include"Mouse.h"
#include"Block.h"
#include"inline.h"
#include<time.h>
class CGameManager
{

public:
	CGameManager(HINSTANCE inst);
	~CGameManager();
public:
	void render(HDC hdc);
	void progress();//매프레임마다 호출.
	void setMouseDirection(UINT msg, const int &mx, const int &my);//방향세팅.
	void makeBlock();
	void checkInBoardBlock();//보드안에 블럭있는가 체크
	void update();
	void sortFunc(const int &direction);
	void move();
	void FindHighType();
	e_BITMAP_TYPE getHighType(){ return m_iHighType; }
	void setHighType(const e_BITMAP_TYPE&num){ m_iHighType = num; }
	bool getBlockMovingState()const { return m_bBlockIsMoving; }
	void setBlockMovingState(bool b) { m_bBlockIsMoving = b; }

private:
	CBoard* m_pBoard;
	CMouse* m_pMouse;
	CBlock* m_pBlockArr[name_BLOCK_INFO::MAX_BLOCK_NUM];
	HINSTANCE& m_g_hinst;
private:
	int m_iMouseDirection;
	int m_iBlockNum;
	e_BITMAP_TYPE m_iHighType;
	float m_fFrametime = 0;
	bool m_bBlockIsMoving = false;
public:
	

};


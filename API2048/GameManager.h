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
	void timer();
	void sortFunc(const int &direction);
	void move();
	void FindHighType();
	int getHighType(){ return m_iHighType; }
	void setHighType(const int &num){ m_iHighType = num; }
private:
	CBoard* m_pBoard;
	CMouse* m_pMouse;
	CBlock* m_pBlockArr[name_BLOCK_INFO::MAX_BLOCK_NUM];
	HINSTANCE m_g_hinst;
private:
	int m_iMouseDirection;
	int m_iBlockNum;
	int m_iHighType;
	float m_fFrametime = 0;
public:
	

};


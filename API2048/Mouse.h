#pragma once
#include<Windows.h>
#include"enum.h"
class CMouse
{
public:
	CMouse();
	~CMouse();


public:
	void setDirection(const int &DestRight,const int &DestBotoom);//0,0부터 사각형right,bottom넘기기.
private:
	int m_iStartX;
	int m_iEndX;
	int m_iStartY;
	int m_iEndY;
	int m_iDirection;

	bool m_bDirectionReady;
public:
	//getter
	int getStartX(){ return m_iStartX; };
	int getStartY(){ return m_iStartY; };
	int getEndX(){ return m_iEndX;};
	int getEndY(){ return m_iEndY; };
	int getDirection(){ return m_iDirection; }
public:
	//setter
	void setStartX(const int &x){ m_iStartX = x; };
	void setStartY(const int &y){ m_iStartY = y; };
	void setEndX(const int &x){ m_iEndX = x; };
	void setEndY(const int &y){ m_iEndY = y; };
	void setDIrec(const int &direction){ m_iDirection = direction; }
};


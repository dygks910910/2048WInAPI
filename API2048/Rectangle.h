#pragma once
#include<Windows.h>
#include"define.h"
#include"Block.h"
class CRectangle
{
public://getter
	CBlock* getBlockAddr(){ return m_pBlock; }
	POINT getPosition(){ return m_poPosition; };
	bool getCheckBlock(){ return m_bCheckBlock; };
public://setter
	void setBlockAddr(CBlock *pBlock){ m_pBlock = pBlock; }
	void setCheckBlock(const bool &b){ m_bCheckBlock = b; };
	void setPosition(const int &x, const int &y){ m_poPosition.x = x; m_poPosition.y = y; }
public:
	void render(HDC hdc);

public:
	CRectangle(const POINT &position);
	~CRectangle();

private:
	POINT m_poPosition;
	int m_iWidth;
	bool m_bCheckBlock;
	CBlock* m_pBlock;
};


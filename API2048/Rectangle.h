#pragma once
#include<Windows.h>
#include"define.h"
#include"Vector2.h"
class CRectangle
{
public://getter
	CVector2 getPosition(){ return m_poPosition; };
	bool getCheckBlock(){ return m_bCheckBlock; };
public://setter
	void setCheckBlock(const bool &b){ m_bCheckBlock = b; };
	void setPosition(const int &x, const int &y){ m_poPosition.x = x; m_poPosition.y = y; }
	CVector2 GetPosition()const { return m_poPosition; }
public:
	void render(HDC hdc);

public:
	CRectangle(const CVector2&position);
	~CRectangle();

private:
	CVector2 m_poPosition;
	int m_iWidth;
	bool m_bCheckBlock;
};


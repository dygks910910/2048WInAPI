#pragma once
#include<Windows.h>
#include"define.h"
#include"enum.h"
#include"resource.h"
typedef struct tag_IndexInfo
{
	int y;
	int x;
}INDEXINFO;
class CBlock
{

public:
	void render(HDC hdc);
	void move(const int &direction, const POINT &position);
public:
	CBlock(const POINT &position, HINSTANCE inst);
	~CBlock();
private:
	HDC memdc;
	HBITMAP m_bitmap[11];
	POINT m_poPostion;
	INDEXINFO m_indexInfo;//보드의 위치인덱스.
	int m_iBitmapType;
	int m_idestType;
public:
	//getter
	int getBitmapType(){ return m_iBitmapType; }
	POINT getPosition(){ return m_poPostion; };
	INDEXINFO getIndexInfo(){ return m_indexInfo; };
	//setter
	void setBitmapType(const int &type){ m_iBitmapType = type; }
	void setIndexInfo(const int &x, const int &y){ m_indexInfo.x = x; m_indexInfo.y = y; }
	void setPosition(const int &x, const int &y){ m_poPostion.x = x; m_poPostion.y = y;}
};


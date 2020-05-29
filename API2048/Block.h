#pragma once
#include<Windows.h>
#include"define.h"
#include"enum.h"
#include"resource.h"
#include"Vector2.h"
typedef struct tag_IndexInfo
{
	int y;
	int x;
}INDEXINFO;
class CBlock
{

public:
	void render(HDC hdc);
	void move(const e_DIRECTION& direction, const POINT &position);
public:
	CBlock(const CVector2&position, HINSTANCE inst);
	~CBlock();
private:
	static HBITMAP m_bitmap[11];
	CVector2 m_poPostion;
	INDEXINFO m_indexInfo;//보드의 위치인덱스.
	e_BITMAP_TYPE m_iBitmapType;
	bool m_bIsMoving = false;
public:
	//getter
	e_BITMAP_TYPE getBitmapType(){ return m_iBitmapType; }
	CVector2 getPosition(){ return m_poPostion; };
	INDEXINFO getIndexInfo(){ return m_indexInfo; };
	bool getisMoving() { return m_bIsMoving; }
	//setter
	void setBitmapType(const e_BITMAP_TYPE&type){ m_iBitmapType = type; }
	void setIndexInfo(const int &x, const int &y){ m_indexInfo.x = x; m_indexInfo.y = y; }
	void setPosition(const int &x, const int &y){ m_poPostion.x = x; m_poPostion.y = y;}
	void setIsMoving(bool b) { m_bIsMoving = b; }
public:
	const int BLOCK_MOVE_SPEED = 20;

};


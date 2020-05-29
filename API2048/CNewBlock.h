#pragma once
#include<Windows.h>
#include"enum.h"
#include"Vector2.h"
#include"Rectangle.h"
struct POINT2D
{
	int x, y;
	POINT2D(int _x, int _y) { x = _x; y = _y; }
	bool operator==(POINT2D a)
	{
		return a.x == x && a.y == y;
	}
};
class CNewBlock
{
public:
	CNewBlock();
	CNewBlock(CRectangle& vec);

	~CNewBlock();
	bool InitBitMap();
	void Render(HDC hdc);
	e_BITMAP_TYPE GetBitmapType() { return m_iBitmapType; }
	const CVector2* GetPosition() { return &m_poPostion; };
	void Update();
	void MoveTo();
	void SetMotherRect(CRectangle& vec) { m_motherRect = vec; }
	CRectangle& GetMotherRect() { return m_motherRect; }
private:
	static HBITMAP m_bitmap[11];
	CVector2 m_poPostion;
	e_BITMAP_TYPE m_iBitmapType;
	e_DIRECTION m_eDirection;
	CRectangle& m_motherRect;

};


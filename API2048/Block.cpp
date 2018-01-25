#include "Block.h"

CBlock::CBlock(const POINT &position,HINSTANCE inst) : m_poPostion(position), m_indexInfo({0,0})
{
	m_bitmap[0] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP2));
	m_bitmap[1] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP3));
	m_bitmap[2] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP4));
	m_bitmap[3] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP5));
	m_bitmap[4] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP6));
	m_bitmap[5] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP7));
	m_bitmap[6] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP8));
	m_bitmap[7] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP9));
	m_bitmap[8] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP10));
	m_bitmap[9] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP11));
	m_bitmap[10] = LoadBitmap(inst, MAKEINTRESOURCE(IDB_BITMAP12));
	m_iBitmapType = e_BITMAP_TYPE::TYPE1;
}


CBlock::~CBlock()
{
}

void CBlock::render(HDC hdc)
{
	HBITMAP oldbmp;
	memdc = CreateCompatibleDC(hdc);
	oldbmp = (HBITMAP)SelectObject(memdc, m_bitmap[m_iBitmapType]);
	StretchBlt(hdc, m_poPostion.x - name_RECT_INFO::RECT_WIDTH / 2+1,
		m_poPostion.y - name_RECT_INFO::RECT_WIDTH / 2+1
		, name_RECT_INFO::RECT_WIDTH-1,
		name_RECT_INFO::RECT_WIDTH-1, memdc, 0, 0,48,48, SRCCOPY);
	SelectObject(memdc, oldbmp);
	DeleteDC(memdc);
	if (m_idestType == m_iBitmapType)
	{
		int a;
		//a = MessageBox()
	}
	/*Ellipse(hdc, m_poPostion.x - name_RECT_INFO::RECT_WIDTH / 2, m_poPostion.y - name_RECT_INFO::RECT_WIDTH / 2,
		m_poPostion.x + name_RECT_INFO::RECT_WIDTH / 2, m_poPostion.y + name_RECT_INFO::RECT_WIDTH / 2);*/
	/*char buff[20];
	wsprintf(buff, "%d,%d,%d,%d", m_poPostion.x, m_poPostion.y,m_indexInfo.y,m_indexInfo.x);
	TextOut(hdc, m_poPostion.x, m_poPostion.y, buff, strlen(buff));*/
}

void CBlock::move(const int &direction, const POINT &position)
{
	switch (direction)
	{
		case e_DIRECTION::DOWN:
			if (m_poPostion.y < position.y)
				m_poPostion.y += 20;
			break;
		case e_DIRECTION::UP:
			if (m_poPostion.y > position.y)
				m_poPostion.y -= 20;
			break;
		case e_DIRECTION::LEFT:
			if (m_poPostion.x > position.x)
				m_poPostion.x -= 20;
			break;
		case e_DIRECTION::RIGHT:
			if (m_poPostion.x < position.x)
				m_poPostion.x += 20;
			break;
		case e_DIRECTION::STOP:
			break;
	}
}

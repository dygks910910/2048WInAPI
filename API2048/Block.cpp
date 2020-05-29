#include "Block.h"
HBITMAP CBlock::m_bitmap[11] = { NULL };

CBlock::CBlock(const CVector2&position,HINSTANCE inst) : m_poPostion(position), m_indexInfo({0,0})
{
	if (m_bitmap[0] == NULL)
	{
		for (int j = 0,i = IDB_BITMAP1; i < IDB_BITMAP11; ++i,++j)
		{
			m_bitmap[j] = LoadBitmap(inst, MAKEINTRESOURCE(i));
			if (m_bitmap[j] == NULL) 
			{
				MessageBox(0, "비트맵 로드실패", "비트맵 로드실패", 0);
				break;
			}
		}
	}
	m_iBitmapType = e_BITMAP_TYPE::TYPE1;
}


CBlock::~CBlock()
{
}

void CBlock::render(HDC hdc)
{
	HBITMAP oldbmp;
	HDC memdc;
	memdc = CreateCompatibleDC(hdc);
	oldbmp = (HBITMAP)SelectObject(memdc, m_bitmap[static_cast<int>(m_iBitmapType)]);
	StretchBlt(hdc, m_poPostion.x - name_RECT_INFO::RECT_WIDTH / 2+1,
		m_poPostion.y - name_RECT_INFO::RECT_WIDTH / 2+1
		, name_RECT_INFO::RECT_WIDTH-1,
		name_RECT_INFO::RECT_WIDTH-1, memdc, 0, 0,48,48, SRCCOPY);
	SelectObject(memdc, oldbmp);
	DeleteDC(memdc);
	
	/*Ellipse(hdc, m_poPostion.x - name_RECT_INFO::RECT_WIDTH / 2, m_poPostion.y - name_RECT_INFO::RECT_WIDTH / 2,
		m_poPostion.x + name_RECT_INFO::RECT_WIDTH / 2, m_poPostion.y + name_RECT_INFO::RECT_WIDTH / 2);*/
	/*char buff[20];
	wsprintf(buff, "%d,%d,%d,%d", m_poPostion.x, m_poPostion.y,m_indexInfo.y,m_indexInfo.x);
	TextOut(hdc, m_poPostion.x, m_poPostion.y, buff, strlen(buff));*/
}

void CBlock::move(const e_DIRECTION& direction, const POINT &position)
{
	switch (direction)
	{
		case e_DIRECTION::DOWN:
			if (m_poPostion.y < position.y)
			{
				m_poPostion.y += 20;
				m_bIsMoving = true;
				if (m_poPostion.y == position.y)
				{
					m_poPostion.y = position.y;
					m_bIsMoving = false;
				}
			}
			
			break;
		case e_DIRECTION::UP:
			if (m_poPostion.y > position.y)
			{
				m_poPostion.y -= 20;
				m_bIsMoving = true;
				if (m_poPostion.y == position.y)
				{
					m_poPostion.y = position.y;
					m_bIsMoving = false;
				}
			}
			
			break;
		case e_DIRECTION::LEFT:
			if (m_poPostion.x > position.x)
			{
				m_poPostion.x -= 20;
				m_bIsMoving = true;
				if (m_poPostion.x == position.x)
				{
					m_poPostion.x = position.x;
					m_bIsMoving = false;
				}
			}
			
			break;
		case e_DIRECTION::RIGHT:
			if (m_poPostion.x < position.x)
			{
				m_poPostion.x += 20;
				m_bIsMoving = true;
				if (m_poPostion.x == position.x)
				{
					m_poPostion.x = position.x;
					m_bIsMoving = false;
				}
			}
			break;
		case e_DIRECTION::STOP:
			m_bIsMoving = false;
			break;
	}
}

#include "CNewBlock.h"
#include"define.h"
#include"resource.h"
#include"CNewBoard.h"
HBITMAP CNewBlock::m_bitmap[11] = { NULL };


CNewBlock::CNewBlock(CRectangle& vec):
m_iBitmapType(e_BITMAP_TYPE::TYPE1),
m_poPostion(vec.GetPosition()),
m_eDirection(e_DIRECTION::STOP),
m_motherRect(vec)
{
	InitBitMap();
}

CNewBlock::~CNewBlock()
{
}

bool CNewBlock::InitBitMap()
{
	if (m_bitmap[0] == NULL)
		for (int j = 0, i = IDB_BITMAP1; i < IDB_BITMAP11; ++i, ++j)
		{
			m_bitmap[j] = LoadBitmap(g_hInst, MAKEINTRESOURCE(i));
			if (m_bitmap[j] == NULL)
			{
				MessageBox(0, "비트맵 로드실패", "비트맵 로드실패", 0);
				return false;
			}
		}
	return true;
}

void CNewBlock::Render(HDC hdc)
{
	HBITMAP oldbmp;
	HDC memdc;
	memdc = CreateCompatibleDC(hdc);
	oldbmp = (HBITMAP)SelectObject(memdc, m_bitmap[static_cast<int>(m_iBitmapType)]);
	StretchBlt(hdc, m_poPostion.x - name_RECT_INFO::RECT_WIDTH / 2 + 1,
		m_poPostion.y - name_RECT_INFO::RECT_WIDTH / 2 + 1
		, name_RECT_INFO::RECT_WIDTH - 1,
		name_RECT_INFO::RECT_WIDTH - 1, memdc, 0, 0, 48, 48, SRCCOPY);
	SelectObject(memdc, oldbmp);
	DeleteDC(memdc);
}

void CNewBlock::Update()
{
	if (isMoving)
	{
		isMoving = MoveTo();
	}
}

bool CNewBlock::MoveTo()
{
	if (m_poPostion == m_motherRect.GetPosition())
		return false;
	m_poPostion = CVector2::Lerp(m_poPostion, m_motherRect.GetPosition(),0.01f);
	
	return true;
}

void CNewBlock::DeleteBmpFile()
{
	for (int j = 0; j < IDB_BITMAP11- IDB_BITMAP1;  ++j)
	{
		DeleteObject(m_bitmap[j]);
	}
}

void CNewBlock::onNotify(e_Event event)
{
	switch (event)
	{
	case e_Event::BLOCK_STOP:
		isMoving = false;
		break;
	case e_Event::BLOCK_MOVE:
		isMoving = true;
		isFusioned = false;
		break;
	case e_Event::BMP_LEVELUP:
	{
		e_BITMAP_TYPE type = GetBitmapType();
		int iTmp = static_cast<int>(type) + 1;
		m_iBitmapType = static_cast<e_BITMAP_TYPE>(iTmp);
	}
		break;
	default:
		break;
	}
}

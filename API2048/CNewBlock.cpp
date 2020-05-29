#include "CNewBlock.h"
#include"define.h"
#include"resource.h"
HBITMAP CNewBlock::m_bitmap[11] = { NULL };


CNewBlock::CNewBlock(CRectangle& vec) :
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
	{
		for (int j = 0, i = IDB_BITMAP1; i < IDB_BITMAP11; ++i, ++j)
		{
			m_bitmap[j] = LoadBitmap(g_hInst, MAKEINTRESOURCE(i));
			if (m_bitmap[j] == NULL)
			{
				MessageBox(0, "비트맵 로드실패", "비트맵 로드실패", 0);
				return false;
			}
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
		MoveTo();
}

void CNewBlock::MoveTo()
{
	m_poPostion = CVector2::Lerp(m_poPostion, m_motherRect.GetPosition(), g_timer.GetDeltaTime().count());
}

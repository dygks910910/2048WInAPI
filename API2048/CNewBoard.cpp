#include "CNewBoard.h"
CNewBoard::CNewBoard()
{
	m_vecRectBoard.reserve(16);
	m_vecBlockList.reserve(16);
	CVector2 poTemp;
	for (int i = 0; i < name_BOARD_ARR_INFO::BOARD_INDEX_X; i++)
	{
		for (int j = 0; j < name_BOARD_ARR_INFO::BOARD_INDEX_Y; j++)
		{
			poTemp.x = j * name_RECT_INFO::RECT_WIDTH + name_RECT_INFO::RECT_WIDTH;
			poTemp.y = i * name_RECT_INFO::RECT_WIDTH + name_RECT_INFO::RECT_WIDTH;
			m_vecRectBoard[i+j*4] = new CRectangle(poTemp);
		}
	}

}

CNewBoard::~CNewBoard()
{
	for (int i = 0; i < m_vecRectBoard.size(); ++i)
	{
		SAFE_DELETE(m_vecRectBoard[i]);
	}
	for (int i = 0; i < m_vecBlockList.size(); ++i)
	{
		SAFE_DELETE(m_vecBlockList[i]);
	}
}

void CNewBoard::Render(HDC hdc)
{
	for (int i = 0; i < m_vecRectBoard.size(); ++i)
	{
		if (m_vecRectBoard[i] != nullptr)
			m_vecRectBoard[i]->render(hdc);
	}
	for (int i = 0; i < m_vecBlockList.size(); ++i)
	{
		if(m_vecBlockList[i] != nullptr)
			m_vecBlockList[i]->Render(hdc);
	}
	RECT a, b;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			a.left = 500 + i *10;
			a.top = 100;
			a.right = a.left + 10;
			a.top = a.top + 10;

			b.left = 700 + i*10;
			b.top = 100;
			b.right = b.left + 10;
			b.top = b.top + 10;

			TextOut(hdc, a.left, a.top, m_vecBlockList[i + j * 4] == nullptr ? "0" : "1", 2);
			TextOut(hdc, b.left, b.top, m_vecBlockList[i + j * 4] == nullptr ? "0" : "1", 2);

		}
	}
}

void CNewBoard::Update()
{
	
	for (int i = 0; i < m_vecBlockList.size(); ++i)
	{
		if (m_vecBlockList[i] != nullptr)
			m_vecBlockList[i]->Update();
	}
}

bool CNewBoard::CheckBlockByIdx(int x, int y)
{
	if (x < name_BOARD_ARR_INFO::BOARD_INDEX_X ||
		y < name_BOARD_ARR_INFO::BOARD_INDEX_Y ||
		x > 0 ||
		y > 0)
		return false;
	return m_vecRectBoard[x + y * 4]->getCheckBlock();
}
bool CNewBoard::CalcBlockMove(e_DIRECTION dir)
{
	int rowOut = 0, colOut = 0;
	bool bSameBmpType;
	switch (dir)
	{
	case e_DIRECTION::LEFT:
	{
		for (int col = 0; col < name_BOARD_ARR_INFO::BOARD_INDEX_Y; ++col)
		{
			//1열부터 먼저 계산.
			for (int row = 1; row < name_BOARD_ARR_INFO::BOARD_INDEX_X; ++row)
			{
				if (MovePossible(row, col, rowOut, colOut, dir, bSameBmpType))
				{
					auto pTmp = m_vecBlockList[rowOut + colOut * name_BOARD_ARR_INFO::BOARD_INDEX_Y];
					pTmp->SetMotherRect(*m_vecRectBoard[rowOut + colOut * name_BOARD_ARR_INFO::BOARD_INDEX_Y]);
					
				}
			}
		}
	}
		break;
	case e_DIRECTION::RIGHT:
		for (int col = 0; col < name_BOARD_ARR_INFO::BOARD_INDEX_Y; ++col)
		{
			//4열부터 먼저 계산
			for (int row = name_BOARD_ARR_INFO::BOARD_INDEX_X-1; row >= 0 ; --row)
			{
				if (MovePossible(row, col, rowOut, colOut, dir, bSameBmpType))
				{
					m_vecBlockList[rowOut + colOut * name_BOARD_ARR_INFO::BOARD_INDEX_Y]->SetMotherRect(
						*m_vecRectBoard[rowOut + colOut * name_BOARD_ARR_INFO::BOARD_INDEX_Y]
					);

				}
			}
		}
		break;
	case e_DIRECTION::UP:
		//1행부터 먼저 계산
		break;
	case e_DIRECTION::DOWN:
		//4행부터 먼저 계산.
		break;
	case e_DIRECTION::STOP:
		break;
	default:
		break;
	}
	return true;
}
bool CNewBoard::MovePossible(int row, int col, OUT int& rowOut, OUT int& colOut, e_DIRECTION eDir,OUT bool &bSameBmpType)
{
	if (BIGOREQUALTHANZERO_SMALLTHENY(row,name_BOARD_ARR_INFO::BOARD_INDEX_X) &&
		BIGOREQUALTHANZERO_SMALLTHENY(col, name_BOARD_ARR_INFO::BOARD_INDEX_Y))
		return false;
	if (m_vecBlockList[row + col * name_BOARD_ARR_INFO::BOARD_INDEX_Y] == nullptr)
		return false;
	rowOut = row;
	colOut = col;
	switch (eDir)
	{
	case e_DIRECTION::LEFT:
	{
		for (int i = row; i >= 0; --i)
		{
			if (m_vecBlockList[i + col * 4] == nullptr)
				rowOut = i;
			else
			{
				if (EqualBitmapType(m_vecBlockList[i + col * 4],
					m_vecBlockList[row + col * 4]))
				{
					rowOut -= 1;
					bSameBmpType = true;
				}
			}
		}
	}
		break;
	case e_DIRECTION::RIGHT:
	{
		for (int i = row; i < name_BOARD_ARR_INFO::BOARD_INDEX_X; ++i)
		{
			if (m_vecBlockList[i + col * 4] == nullptr)
				rowOut = i;
			else
			{
				if (EqualBitmapType(m_vecBlockList[i + col * 4],
					m_vecBlockList[row + col * 4]))
				{
					rowOut += 1;
					bSameBmpType = true;
				}
				
			}
		}
	}
		break;
	case e_DIRECTION::UP:
	{
		for (int i = col; i >= 0; --i)
		{
			if (m_vecBlockList[row + i * 4] == nullptr)
				colOut = i;
			else
			{
				if (EqualBitmapType(m_vecBlockList[row + i * 4],
					m_vecBlockList[row + col * 4]))
				{
					colOut -= 1;
					bSameBmpType = true;
				}

			}
		}
	}
		break;
	case e_DIRECTION::DOWN:
	{
		for (int i = col; i < name_BOARD_ARR_INFO::BOARD_INDEX_X; ++i)
		{
			if (m_vecBlockList[row + i * 4] == nullptr)
				colOut = i;
			else
			{
				if (EqualBitmapType(m_vecBlockList[row + i * 4],
					m_vecBlockList[row + col * 4]))
				{
					colOut += 1;
					bSameBmpType = true;
				}

			}
		}
	}
		break;
	case e_DIRECTION::STOP:
		break;
	default:
		break;
	}
	return true;
}
bool CNewBoard::EqualBitmapType(CNewBlock* blc1, CNewBlock* blc2)
{
	e_BITMAP_TYPE eBTypeDest = blc1->GetBitmapType();
	e_BITMAP_TYPE eBTypeSrc = blc2->GetBitmapType();
	return eBTypeDest == eBTypeSrc ? true : false;
}
bool CNewBoard::MakeBlock()
{
	int iCountBlock = 0;
	for (int i = 0; i < name_BLOCK_INFO::MAX_BLOCK_NUM; ++i)
	{
		if (m_vecBlockList[i] != nullptr)
			iCountBlock++;
	}
	if (iCountBlock == name_BLOCK_INFO::MAX_BLOCK_NUM)
		return false;
	while (1)
	{
		int row = rand() % name_BOARD_ARR_INFO::BOARD_INDEX_X;
		int col = rand() % name_BOARD_ARR_INFO::BOARD_INDEX_Y;
		bool bExist = CheckBlockByIdx(row, col);
		if (bExist)
			continue;
		else
		{
			m_vecBlockList[row + col * name_BOARD_ARR_INFO::BOARD_INDEX_X] =
				new CNewBlock(*m_vecRectBoard[row + col * name_BOARD_ARR_INFO::BOARD_INDEX_X]);
			break;
		}
	}
	
}
//
//void CNewBoard::BlockMoveTo(int x, int y, CVector2 pos)
//{
//	CVector2 destVec = m_vecRectBoard[x + y * 4]->getPosition();
//
//}

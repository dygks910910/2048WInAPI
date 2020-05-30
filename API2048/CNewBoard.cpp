#include "CNewBoard.h"
CNewBoard::CNewBoard()
{
	m_vecRectBoard.resize(16);
	m_vecBlockList.resize(16);
	CVector2 poTemp;
	for (int iCol = 0; iCol < BD_INFO::BOARD_INDEX_X; iCol++)
	{
		for (int iRaw = 0; iRaw < BD_INFO::MAXY; iRaw++)
		{
			poTemp.x = iRaw * name_RECT_INFO::RECT_WIDTH + name_RECT_INFO::RECT_WIDTH;
			poTemp.y = iCol * name_RECT_INFO::RECT_WIDTH + name_RECT_INFO::RECT_WIDTH;
			m_vecRectBoard[iRaw+ iCol *4] = new CRectangle(poTemp);
		}
	}

	MakeBlock();
	MakeBlock();

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
	CNewBlock::DeleteBmpFile();
}

void CNewBoard::Render(HDC hdc)
{
	for (int i = 0; i < m_vecRectBoard.size(); ++i)
	{
			m_vecRectBoard[i]->render(hdc);
	}
	for (int i = 0; i < m_vecBlockList.size(); ++i)
	{
		if(m_vecBlockList[i] != nullptr)
			m_vecBlockList[i]->Render(hdc);
	}
	RECT a, b;
	for (int iCol = 0; iCol < 4; ++iCol)
	{
		for (int iRow = 0; iRow < 4; ++iRow)
		{
			a.left = 400 + iRow *15;
			a.top = 100 + iCol * 15;

			b.left = 400 + iRow * 15;
			b.top = 300 + iCol * 15;

			TextOut(hdc, a.left, a.top, m_vecBlockList[iRow + iCol * 4] == nullptr ? "0" : "1", 1);
			TextOut(hdc, b.left, b.top, m_vecRectBoard[iRow + iCol * 4] == nullptr ? "0" : "1", 1);

		}
	}
}

void CNewBoard::Update(e_DIRECTION eDir)
{
	//CalcBlockMove(eDir);
	//Notify(e_Event::BLOCK_MOVE);
	for (int i = 0; i < m_vecBlockList.size(); ++i)
	{
		if (m_vecBlockList[i] != nullptr)
			m_vecBlockList[i]->Update();
	}
	
}

bool CNewBoard::CheckBlockByIdx(int x, int y)
{
	return m_vecBlockList[x + y * 4]!= nullptr;
}
bool CNewBoard::CalcBlockMove(e_DIRECTION dir)
{
	bool bSameBmpType =false;
	ChangeBlockInfo info;
	ZeroMemory(&info, sizeof(info));
	switch (dir)
	{
	case e_DIRECTION::LEFT:
	{
		for (int col = 0; col < BD_INFO::MAXY; ++col)
		{
			//1열부터 먼저 계산.
			for (int row = 0; row < BD_INFO::BOARD_INDEX_X; ++row)
			{
				ZeroMemory(&info, sizeof(info));
				if (MovePossible(row, col, dir, info))
				{
					if (info.isSameBitmap)
					{
						//메모리 해제해주기.
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetIsFusioned(true);
						removeObserver(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);
						SAFE_DELETE(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);
						
						//비트맵 바꿔주기
						int iBmpType = static_cast<int>(m_vecBlockList[row+ col* BD_INFO::MAXY]->GetBitmapType());
						e_BITMAP_TYPE eType = static_cast<e_BITMAP_TYPE>(iBmpType += 1);
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetBitmapType(eType);
						
						
						//백보드 Rect세팅
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetMotherRect(
							*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]
						);
						//보드판 정리.
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
					}
					else
					{
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						pTmp->SetMotherRect(*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]);
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
						//return true;
					}
				}
			}
		}
	}
		break;
	case e_DIRECTION::RIGHT:
		for (int col = BD_INFO::BOARD_INDEX_X - 1; col >= 0; --col)
		{
			//4열부터 먼저 계산
			for (int row = BD_INFO::BOARD_INDEX_X-1; row >= 0 ; --row)
			{
				ZeroMemory(&info, sizeof(info));
				if (MovePossible(row, col, dir, info))
				{
					if (info.isSameBitmap)
					{
						//메모리 해제해주기.
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetIsFusioned(true);
						removeObserver(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);
						SAFE_DELETE(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);

						//비트맵 바꿔주기
						int iBmpType = static_cast<int>(m_vecBlockList[row + col * BD_INFO::MAXY]->GetBitmapType());
						e_BITMAP_TYPE eType = static_cast<e_BITMAP_TYPE>(iBmpType += 1);
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetBitmapType(eType);


						//백보드 Rect세팅
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetMotherRect(
							*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]
						);
						//보드판 정리.
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
					}
					else
					{
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						pTmp->SetMotherRect(*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]);
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
						//return true;
					}

				}
				
			}
		}
		break;
	case e_DIRECTION::UP:
		for (int col = 0; col < BD_INFO::MAXY; ++col)
		{
			//1열부터 먼저 계산.
			for (int row = 0; row < BD_INFO::BOARD_INDEX_X; ++row)
			{
				ZeroMemory(&info, sizeof(info));
				if (MovePossible(row, col, dir, info))
				{
					if (info.isSameBitmap)
					{
						//메모리 해제해주기.
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetIsFusioned(true);
						removeObserver(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);
						SAFE_DELETE(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);

						//비트맵 바꿔주기
						int iBmpType = static_cast<int>(m_vecBlockList[row + col * BD_INFO::MAXY]->GetBitmapType());
						e_BITMAP_TYPE eType = static_cast<e_BITMAP_TYPE>(iBmpType += 1);
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetBitmapType(eType);


						//백보드 Rect세팅
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetMotherRect(
							*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]
						);
						//보드판 정리.
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
					}
					else
					{
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						pTmp->SetMotherRect(*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]);
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
						//return true;
					}
				}

			}
		}
		break;
	case e_DIRECTION::DOWN:
		//4행부터 먼저 계산.
		for (int col = BD_INFO::BOARD_INDEX_X - 1; col >= 0; --col)
		{
			for (int row = 0; row < BD_INFO::BOARD_INDEX_X; ++row)
			{
				ZeroMemory(&info, sizeof(info));
				if (MovePossible(row, col, dir, info))
				{
					if (info.isSameBitmap)
					{
						//메모리 해제해주기.
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetIsFusioned(true);
						removeObserver(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);
						SAFE_DELETE(m_vecBlockList[info.row + info.col * BD_INFO::MAXY]);

						//비트맵 바꿔주기
						int iBmpType = static_cast<int>(m_vecBlockList[row + col * BD_INFO::MAXY]->GetBitmapType());
						e_BITMAP_TYPE eType = static_cast<e_BITMAP_TYPE>(iBmpType += 1);
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetBitmapType(eType);


						//백보드 Rect세팅
						m_vecBlockList[row + col * BD_INFO::MAXY]->SetMotherRect(
							*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]
						);
						//보드판 정리.
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
					}
					else
					{
						auto pTmp = m_vecBlockList[row + col * BD_INFO::MAXY];
						pTmp->SetMotherRect(*m_vecRectBoard[info.row + info.col * BD_INFO::MAXY]);
						m_vecBlockList[info.row + info.col * BD_INFO::MAXY] = pTmp;
						m_vecBlockList[row + col * BD_INFO::MAXY] = nullptr;
						//return true;
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
bool CNewBoard::MovePossible(int row, int col,e_DIRECTION eDir,OUT ChangeBlockInfo& info)
{
	if (BIGOREQUALTHANZERO_SMALLTHENY(row,BD_INFO::BOARD_INDEX_X) &&
		BIGOREQUALTHANZERO_SMALLTHENY(col, BD_INFO::MAXY))
		return false;
	if (m_vecBlockList[row + col * BD_INFO::MAXY] == nullptr)
		return false;
	info.row = row;
	info.col = col;
	switch (eDir)
	{
	case e_DIRECTION::LEFT:
	{
		for (int i = row-1; i >= 0; --i)
		{
			if (m_vecBlockList[i + col * 4] == nullptr)
				info.row = i;
			else
				if (EqualBitmapType(m_vecBlockList[i + col * 4],m_vecBlockList[row + col * 4]) 
					&& !(m_vecBlockList[row + col * 4]->GetIsFusioned()) 
					&& !(m_vecBlockList[i + col * 4]->GetIsFusioned()))
				{
					info.row -= 1;
					info.row = info.row;
					info.col = col;
					info.isSameBitmap = true;
					break;
				}
		}
	}
		break;
	case e_DIRECTION::RIGHT:
	{
		for (int i = row+1; i < BD_INFO::BOARD_INDEX_X; ++i)
		{
			if (m_vecBlockList[i + col * 4] == nullptr)
				info.row = i;
			else
			{
				if (EqualBitmapType(m_vecBlockList[i + col * 4],m_vecBlockList[row + col * 4])
					&& !(m_vecBlockList[row + col * 4]->GetIsFusioned()) 
					&&	!(m_vecBlockList[i + col * 4]->GetIsFusioned()))
				{
					info.row += 1;
					info.row = info.row;
					info.col = col;
					info.isSameBitmap = true;
					break;
				}
				
			}
		}
	}
		break;
	case e_DIRECTION::UP:
	{
		for (int i = col-1; i >= 0; --i)
		{
			if (m_vecBlockList[row + i * 4] == nullptr)
				info.col = i;
			else
			{
				if (EqualBitmapType(m_vecBlockList[row + i * 4],m_vecBlockList[row + col * 4]) 
					&&!(m_vecBlockList[row + i * 4]->GetIsFusioned())
					&&!(m_vecBlockList[row + col * 4]->GetIsFusioned()))
				{
					info.col -= 1;
					info.row = row;
					info.col = info.col;
					info.isSameBitmap = true;
				}

			}
		}
	}
		break;
	case e_DIRECTION::DOWN:
	{
		for (int i = col+1; i < BD_INFO::BOARD_INDEX_X; ++i)
		{
			if (m_vecBlockList[row + i * 4] == nullptr)
				info.col = i;
			else
			{
				if (EqualBitmapType(m_vecBlockList[row + i * 4],m_vecBlockList[row + col * 4]) 
					&& !(m_vecBlockList[row + i * 4]->GetIsFusioned()) 
					&& !(m_vecBlockList[row + col * 4]->GetIsFusioned()))
				{
					info.col += 1;
					info.row = row;
					info.col = info.col;
					info.isSameBitmap = true;
					
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

	if (row == info.row && col == info.col)
		return false;
	return true;
}
bool CNewBoard::EqualBitmapType(CNewBlock* blc1, CNewBlock* blc2)
{
	e_BITMAP_TYPE eBTypeDest = blc1->GetBitmapType();
	e_BITMAP_TYPE eBTypeSrc = blc2->GetBitmapType();
	return eBTypeDest == eBTypeSrc;
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
		int row = rand() % (BD_INFO::BOARD_INDEX_X);
		int col = rand() % (BD_INFO::MAXY);
		bool bExist = CheckBlockByIdx(row, col);
		if (bExist)
			continue;
		else
		{
			CNewBlock* pTmpBlock = new CNewBlock(*m_vecRectBoard[row + col * BD_INFO::BOARD_INDEX_X]);
			m_vecBlockList[row + col * BD_INFO::BOARD_INDEX_X] = pTmpBlock;
			AddObserver(pTmpBlock);
			break;
		}
	}
	return true;
}
bool CNewBoard::CheckAllBlockStop()
{
	for (int i = 0; i < m_vecBlockList.size(); ++i)
	{
		if (m_vecBlockList[i] != nullptr)
		{
			bool bTmp = m_vecBlockList[i]->GetisMoving();
			if (bTmp)
				return false;
		}
	}

	return true;
}
//
//void CNewBoard::BlockMoveTo(int x, int y, CVector2 pos)
//{
//	CVector2 destVec = m_vecRectBoard[x + y * 4]->getPosition();
//
//}

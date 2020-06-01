#pragma once
#include<vector>
#include<Windows.h>
#include"Rectangle.h"
#include"CNewBlock.h"
#include"CYHObserver.h"


struct ChangeBlockInfo
{
	int row =-1, col =-1;
	bool isSameBitmap;
};
class CNewBoard : public CSubJect
{
public:
	CNewBoard();
	~CNewBoard();

	void Render(HDC hdc);
	void Update(e_DIRECTION eDir);
	bool CheckBlockByIdx(int x, int y);
	bool CalcBlockMove(e_DIRECTION dir);
	bool MakeBlock();
	bool CheckAllBlockStop();
	void ChangedMouseState(e_Event event) { Notify(event); }
	//void BlockMoveTo(int x, int y, CVector2 pos);
private:
	//아래 두 배열은 서로 의존관계.
	std::vector<CRectangle*> m_vecRectBoard;
	std::vector<CNewBlock*> m_vecBlockList;
private:
	bool MovePossible(int row, int col, e_DIRECTION eDir, OUT ChangeBlockInfo& info);
	bool EqualBitmapType(CNewBlock* blc1, CNewBlock* blc2);
	template<class T>
	void Swap(T a, T b);
	bool CheckFusionPossible(CNewBlock* block1, CNewBlock* block2);
	bool FusionBlock(int row, int col, const ChangeBlockInfo& info);
	void MoveBlock(int row, int col, const ChangeBlockInfo& info);
	// CYHObserver을(를) 통해 상속됨

};

template<class T>
inline void CNewBoard::Swap(T a, T b)
{
	T c = a;
	a = b;
	b = c;
}

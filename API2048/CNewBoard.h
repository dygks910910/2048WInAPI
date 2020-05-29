#pragma once
#include<vector>
#include<Windows.h>
#include"Rectangle.h"
#include"CNewBlock.h"
enum {
	a,b,c,d,e
};
class CNewBoard
{
public:
	CNewBoard();
	~CNewBoard();

	void Render(HDC hdc);
	void Update();
	bool CheckBlockByIdx(int x, int y);
	bool CalcBlockMove(e_DIRECTION dir);
	bool MakeBlock();
	//void BlockMoveTo(int x, int y, CVector2 pos);
private:
	//아래 두 배열은 서로 의존관계.
	std::vector<CRectangle*> m_vecRectBoard;
	std::vector<CNewBlock*> m_vecBlockList;
private:
	bool MovePossible(int row, int col, OUT int& rowOut, OUT int& colOut, e_DIRECTION eDir,OUT bool &bSameBmpType);
	bool EqualBitmapType(CNewBlock* blc1, CNewBlock* blc2);
	template<class T>
	void Swap(T a, T b);

};

template<class T>
inline void CNewBoard::Swap(T a, T b)
{
	T c = a;
	a = b;
	b = c;
}

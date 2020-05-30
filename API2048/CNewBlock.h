#pragma once
#include<Windows.h>
#include"enum.h"
#include"Vector2.h"
#include"Rectangle.h"
#include"CYHObserver.h"
class CNewBoard;

class CNewBlock : public CYHObserver
{
public:
	CNewBlock(CRectangle& vec);

	~CNewBlock();
	bool InitBitMap();
	void Render(HDC hdc);
	e_BITMAP_TYPE GetBitmapType() { return m_iBitmapType; }
	void SetBitmapType(e_BITMAP_TYPE type) { m_iBitmapType = type; }

	const CVector2* GetPosition() { return &m_poPostion; };
	void Update();
	bool MoveTo();
	void SetMotherRect(const CRectangle& vec) { m_motherRect = vec; }
	const CRectangle& GetMotherRect() { return m_motherRect; }
	bool GetisMoving()const { return isMoving; }
	bool GetIsFusioned() { return isFusioned; }
	void SetIsFusioned(bool b) { isFusioned = b; }
	static void DeleteBmpFile();
private:
	static HBITMAP m_bitmap[11];
	CVector2 m_poPostion;
	e_BITMAP_TYPE m_iBitmapType;
	e_DIRECTION m_eDirection;
	CRectangle m_motherRect;
	bool isMoving = false;
	bool isFusioned = false;
	// CYHObserver을(를) 통해 상속됨
	virtual void onNotify(e_Event event) override;

};


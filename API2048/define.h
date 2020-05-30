#pragma once
#include"CYHTime.h"
extern HINSTANCE g_hInst;
extern CYHTime* g_timer;
extern double g_dElapsedTime;
#define SAFE_DELETE(x){if(x!= nullptr)delete x;x= nullptr;}
//0보다 x가 같거나 크고 y보다 작다
#define BIGOREQUALTHANZERO_SMALLTHENY(x,y) 0 > x && x < y
namespace name_RECT_INFO
{
	const int RECT_WIDTH = 80;//사각형의 넓이.
}
namespace BD_INFO
{
	const int BOARD_INDEX_X = 4; //X by Y 보드.
	const int MAXY = 4;
}
namespace name_BLOCK_INFO
{
	const int MAX_BLOCK_NUM = BD_INFO::BOARD_INDEX_X*BD_INFO::MAXY; // 블록최대생성개수
}
namespace name_CLIENT_SIZE
{
	const int CLIENT_SIZE_WIDTH = 500;// 윈도우사이즈 조절.
	const int CLIENT_SIZE_HEIGHT = 500;
}
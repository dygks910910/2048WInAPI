#pragma once
#include"CYHTime.h"
extern HINSTANCE g_hInst;
extern CYHTime* g_timer;
extern double g_dElapsedTime;
#define SAFE_DELETE(x){if(x!= nullptr)delete x;x= nullptr;}
//0���� x�� ���ų� ũ�� y���� �۴�
#define BIGOREQUALTHANZERO_SMALLTHENY(x,y) 0 > x && x < y
namespace name_RECT_INFO
{
	const int RECT_WIDTH = 80;//�簢���� ����.
}
namespace BD_INFO
{
	const int BOARD_INDEX_X = 4; //X by Y ����.
	const int MAXY = 4;
}
namespace name_BLOCK_INFO
{
	const int MAX_BLOCK_NUM = BD_INFO::BOARD_INDEX_X*BD_INFO::MAXY; // ����ִ��������
}
namespace name_CLIENT_SIZE
{
	const int CLIENT_SIZE_WIDTH = 500;// ����������� ����.
	const int CLIENT_SIZE_HEIGHT = 500;
}
#pragma once
#include"CYHTime.h"
extern HINSTANCE g_hInst;
extern CYHTime g_timer;

#define SAFE_DELETE(x){if(x!= nullptr)delete x;x= nullptr;}
//0���� x�� ���ų� ũ�� y���� �۴�
#define BIGOREQUALTHANZERO_SMALLTHENY(x,y) 0 >= x && x < y
namespace name_RECT_INFO
{
	const int RECT_WIDTH = 80;//�簢���� ����.
}
namespace name_BOARD_ARR_INFO
{
	const int BOARD_INDEX_X = 4; //X by Y ����.
	const int BOARD_INDEX_Y = 4;
}
namespace name_BLOCK_INFO
{
	const int MAX_BLOCK_NUM = name_BOARD_ARR_INFO::BOARD_INDEX_X*name_BOARD_ARR_INFO::BOARD_INDEX_Y; // ����ִ��������
}
namespace name_CLIENT_SIZE
{
	const int CLIENT_SIZE_WIDTH = 500;// ����������� ����.
	const int CLIENT_SIZE_HEIGHT = 500;
}
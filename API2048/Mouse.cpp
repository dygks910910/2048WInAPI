#include "Mouse.h"


CMouse::CMouse()
	:m_iStartX(0), m_iStartY(0), m_iEndX(0), m_iEndY(0), m_bDirectionReady(false)
{
	
}


CMouse::~CMouse()
{
}
void CMouse::setDirection(const int &DestRight, const int &DestBotoom)
{

	if (m_iStartX <= m_iEndX && m_iEndX + m_iEndY >= m_iStartX + m_iStartY&& m_iEndY - m_iEndX <= 0)
	{
		m_iDirection = e_DIRECTION::RIGHT;
		return;
	}
	else if (m_iEndX <= m_iStartX && m_iEndX + m_iEndY <= m_iStartX + m_iStartY&& m_iEndY - m_iEndX >= 0)
	{
		m_iDirection = e_DIRECTION::LEFT;
		return;
	}
	else if (m_iStartY >= m_iEndY && m_iEndX+m_iEndY >=m_iEndX+m_iEndY/*m_iStartY >= m_iEndY*/)
	{
		m_iDirection = e_DIRECTION::UP;
		return;
	}
	else if (m_iStartY <= m_iEndY && m_iEndX + m_iEndY <= m_iEndX + m_iEndY)
	{
		m_iDirection = e_DIRECTION::DOWN;
		return;
	}
	//if (m_iStartX < m_iStartY &&m_iStartX + m_iStartY <= DestRight)//аб
	//{
	//	if (m_iEndX + m_iEndY >= DestRight && m_iEndX >= m_iEndY)//©Л
	//	{
	//		m_iDirection = e_DIRECTION::RIGHT;
	//		return;
	//	}
	//}
	//else if (m_iStartX+ m_iStartY >= DestRight && m_iStartX >= m_iStartY)//аб
	//{
	//	if (m_iEndX <= m_iEndY &&m_iEndX + m_iEndY <= DestRight)//©Л
	//	{
	//		m_iDirection = e_DIRECTION::LEFT;
	//		return;
	//	}
	//}
	//else if (m_iStartX + m_iStartY >= DestBotoom && m_iStartY>=m_iStartX)
	//{
	//	if (m_iEndX >= m_iEndY&& m_iEndX + m_iEndY <= DestBotoom)
	//	{
	//		m_iDirection = e_DIRECTION::UP;
	//		return;
	//	}
	//}
	//else if (m_iStartX >= m_iStartY&& m_iStartX + m_iStartY <= DestBotoom)
	//{
	//	if (m_iEndX + m_iEndY >= DestBotoom && m_iEndX <= m_iEndY)
	//	{
	//		m_iDirection = e_DIRECTION::DOWN;
	//		return;
	//	}
	//}
	//m_iDirection = e_DIRECTION::STOP;
}

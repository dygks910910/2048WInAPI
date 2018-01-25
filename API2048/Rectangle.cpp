#include "Rectangle.h"


CRectangle::CRectangle(const POINT &position)
	:m_poPosition(position), m_iWidth(name_RECT_INFO::RECT_WIDTH), m_bCheckBlock(false)
{
	m_pBlock = nullptr;

}


CRectangle::~CRectangle()
{
}
void CRectangle::render(HDC hdc)
{
	//char buff[20] = { 0 };
	
	/*RoundRect(hdc, m_poPosition.x - m_iWidth / 2, m_poPosition.y - m_iWidth / 2,
		m_poPosition.x + m_iWidth / 2, m_poPosition.y + m_iWidth / 2, 10, 10);*/
	Rectangle(hdc, m_poPosition.x - m_iWidth/2, m_poPosition.y - m_iWidth/2,
		m_poPosition.x + m_iWidth/2, m_poPosition.y + m_iWidth/2);
	/*if (m_bCheckBlock)
		TextOut(hdc, m_poPosition.x, m_poPosition.y, "T", strlen("T"));
	else if(!m_bCheckBlock)
		TextOut(hdc, m_poPosition.x, m_poPosition.y, "F", strlen("F"));
*/
}

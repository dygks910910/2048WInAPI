#include "Rectangle.h"


CRectangle::CRectangle(const CVector2&position)
	:m_poPosition(position), m_iWidth(name_RECT_INFO::RECT_WIDTH), m_bCheckBlock(false)
{

}


CRectangle::~CRectangle()
{
}
void CRectangle::render(HDC hdc)
{
	/*RoundRect(hdc, m_poPosition.x - m_iWidth / 2, m_poPosition.y - m_iWidth / 2,
		m_poPosition.x + m_iWidth / 2, m_poPosition.y + m_iWidth / 2, 10, 10);*/
	Rectangle(hdc, m_poPosition.x - m_iWidth/2, m_poPosition.y - m_iWidth/2,
		m_poPosition.x + m_iWidth/2, m_poPosition.y + m_iWidth/2);
}

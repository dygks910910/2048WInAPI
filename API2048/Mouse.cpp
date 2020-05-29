#include "Mouse.h"
#include"Vector2.h"

CMouse::CMouse()
	:m_iStartX(0), m_iStartY(0), m_iEndX(0), m_iEndY(0), m_bDirectionReady(false),m_iDirection(e_DIRECTION::STOP)
{
	
}


CMouse::~CMouse()
{
}
void CMouse::setDirection(const int &DestRight, const int &DestBotoom)
{
	CVector2 startVec = CVector2(m_iStartX, -m_iStartY);
	CVector2 endVec = CVector2(m_iEndX, -m_iEndY);
	//마우스 방향벡터 계산
	CVector2 dirVec = endVec - startVec;
	CVector2 normalDir = normalize(dirVec);
	//x축 방향 벡터
	CVector2 RJudgeVec = startVec;
	RJudgeVec.x += 1;
	RJudgeVec = normalize(RJudgeVec - startVec);
	
	float fCosTheta = dotProduct(normalDir, RJudgeVec);
	float fCrossVal = crossProduct(RJudgeVec, normalDir);
	bool isCW = false;
	
	if (fCrossVal > 0)isCW = false;		  //시계방향
	else			  isCW = true;		  //반시계방향
		
	float fAngle = acos(fCosTheta) * (180/3.1415f);
	if (fAngle > 45 && 135 > fAngle && !isCW)
		m_iDirection = e_DIRECTION::UP;
	else if (fAngle < 45)
		m_iDirection = e_DIRECTION::RIGHT;
	else if (fAngle > 45 && 135 > fAngle && isCW)
		m_iDirection = e_DIRECTION::DOWN;
	else if (fAngle > 135)
		m_iDirection = e_DIRECTION::LEFT;
	else
		m_iDirection = e_DIRECTION::STOP;
}

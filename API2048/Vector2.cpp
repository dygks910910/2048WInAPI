#include "Vector2.h"


CVector2::CVector2() :
	x(0), y(0)
{
}

CVector2::CVector2(float x, float y) :
	x(x), y(y)
{
}


CVector2::CVector2(const CVector2& other)
{
	this->x = other.x;
	this->y = other.y;
}

CVector2::~CVector2()
{
}

void CVector2::createRandomVal()
{
	x = rand();
	y = rand();
}

CVector2 CVector2::operator+(const CVector2& other)
{
	return CVector2(x + other.x, y + other.y);

}

CVector2 CVector2::operator*(const float & other)
{
	return CVector2(x*other, y*other);
}

float CVector2::getLength()const 
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

CVector2 CVector2::Lerp(CVector2 v1, CVector2 v2, float t)
{
	CVector2 ret;
	t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
	ret.x = v1.x + t * (v2.x - v1.x); 
	ret.y = v1.y + t * (v2.y - v1.y);
	return ret;

}

bool CVector2::operator==(const CVector2& v1) const
{

	return fabs(x - v1.x) < 0.1f && fabs(y - v1.y) < 0.1f;
}

bool CVector2::operator!=(const CVector2& v1) const
{
	return !(*this == v1);
}




std::ostream& operator<<(std::ostream & os, const CVector2& vec)
{
	os << "(" << vec.x << "," << vec.y << ")";
	return os;
	// TODO: 여기에 반환 구문을 삽입합니다.
}

CVector2 operator-(const CVector2& v1, const CVector2& v2)
{
	return CVector2(v1.x - v2.x, v1.y - v2.y);

}

/*
2016 / 12 / 4 / 2:35
작성자:박요한(dygks910910@daum.net)
설명:선분ab의 거리를 구해줌.
*/
float distanceVector(const CVector2& a, const CVector2& b)
{
	return sqrt(((b.x-a.x)*(b.x - a.x) ) +((b.y-a.y) *(b.y - a.y)));
}


CVector2 normalize(const CVector2& vec)
{
	float temp = vec.getLength();
	return CVector2(((float)vec.x) / temp, ((float)vec.y) / temp);
}

float dotProduct(const CVector2& vec1, const CVector2& vec2)
{
	//return vec2.getLength() * vec1.getLength();
	return ((vec1.x * vec2.x) + (vec1.y * vec2.y) / (vec1.getLength() * vec2.getLength()));
}

float crossProduct(const CVector2& vec1, const CVector2& vec2)
{
	return (vec1.x*vec2.y) - (vec1.y*vec2.x);
}

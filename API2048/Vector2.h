#pragma once
#include<iostream>
#include<cmath>
/* 
[2016/09/02 18시20분 
작성자 : 박요한(dygks910910@daum.net)]
설명:vector2클래스 구현
*/

class CVector2
{
public:
	float x;
	float y;
public:
	CVector2();
	CVector2(float x,float y);
	CVector2(const CVector2& other);
	~CVector2();
	void createRandomVal();
	CVector2 operator+(const CVector2& other);
	CVector2 operator*(const float& other);
	float getLength()const;
	static CVector2 Lerp(CVector2 v1, CVector2 v2, float t); //선형 보간법
	static CVector2 ZeroVector() { return CVector2(0, 0); }

	bool operator==(const CVector2& v1)const;
	bool operator!=(const CVector2& v1)const;

};
std::ostream& operator<<(std::ostream & os, const CVector2& vec);
CVector2 operator-(const CVector2& v1, const CVector2& v2);

float distanceVector(const CVector2& v1, const CVector2& v2);

CVector2	normalize(const CVector2& vec);
float		dotProduct(const CVector2& vec1, const CVector2& vec2);
//3차원으로 가정하고 Z값은 0으로 계산함.
//return 값은 외적한후의 Z값만 리턴함.
//양수이면 2는1로부터 반시계방향 음수이면 시계방향
float		crossProduct(const CVector2& vec1, const CVector2& vec2);
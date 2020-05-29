#pragma once
#include<iostream>
#include<cmath>
/* 
[2016/09/02 18��20�� 
�ۼ��� : �ڿ���(dygks910910@daum.net)]
����:vector2Ŭ���� ����
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
	static CVector2 Lerp(CVector2 v1, CVector2 v2, float t); //���� ������
	static CVector2 ZeroVector() { return CVector2(0, 0); }

	bool operator==(const CVector2& v1)const;
	bool operator!=(const CVector2& v1)const;

};
std::ostream& operator<<(std::ostream & os, const CVector2& vec);
CVector2 operator-(const CVector2& v1, const CVector2& v2);

float distanceVector(const CVector2& v1, const CVector2& v2);

CVector2	normalize(const CVector2& vec);
float		dotProduct(const CVector2& vec1, const CVector2& vec2);
//3�������� �����ϰ� Z���� 0���� �����.
//return ���� ���������� Z���� ������.
//����̸� 2��1�κ��� �ݽð���� �����̸� �ð����
float		crossProduct(const CVector2& vec1, const CVector2& vec2);
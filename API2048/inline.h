#pragma once
#include<Windows.h>
template<class T>
inline bool checkNull(T t)//null�̸� true �ƴϸ� false
{
	if (t == nullptr)
		return true;
	else
		return false;
}
#pragma once
#include<Windows.h>
template<class T>
inline bool checkNull(T t)//null이면 true 아니면 false
{
	if (t == nullptr)
		return true;
	else
		return false;
}
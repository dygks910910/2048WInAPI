#pragma once
#include<chrono>
class CYHTime
{
public:
	CYHTime();
	~CYHTime();
	void StartTimer();
	double GetDeltaTime();

	void EndTimer();

private:
	std::chrono::system_clock::time_point m_startTp;
	std::chrono::system_clock::time_point m_endTp;

};


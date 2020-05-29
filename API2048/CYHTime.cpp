#include "CYHTime.h"
using namespace std;

CYHTime::CYHTime()
{
}

CYHTime::~CYHTime()
{
}

void CYHTime::StartTimer()
{
	m_startTp = chrono::system_clock::now();
}

std::chrono::duration<double> CYHTime::GetDeltaTime()
{
	return std::chrono::duration<double>(m_endTp - m_startTp);
}

void CYHTime::EndTimer()
{
	m_endTp = chrono::system_clock::now();
}

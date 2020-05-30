#include "CYHObserver.h"

void CSubJect::AddObserver(CYHObserver* observer)
{
	m_vecObservers.push_back(observer);
}

void CSubJect::removeObserver(CYHObserver* observer)
{
	auto iter = std::find(m_vecObservers.begin(), m_vecObservers.end(), observer);
	if (iter != m_vecObservers.end())
		m_vecObservers.erase(iter);
}

void CSubJect::Notify(e_Event event)
{
	for (int i = 0; i < m_vecObservers.size(); ++i)
	{
		m_vecObservers[i]->onNotify(event);
	}
}




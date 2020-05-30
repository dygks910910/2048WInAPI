#pragma once
#include"enum.h"
#include<vector>
class CYHObserver
{
public: 
	virtual ~CYHObserver() {}
	 virtual void onNotify(e_Event event) = 0;

};

class CSubJect
{
private:
	std::vector<CYHObserver*> m_vecObservers;
public:
	void AddObserver(CYHObserver* observer);
	void removeObserver(CYHObserver* observer);
protected:
	void Notify(e_Event event);

};


#pragma once
#include <memory>
#include <KirstenSharedPtr.h>

class CoinAccount
{
private:
	KirstenSharedPtr m_balance = NULL;
	CoinAccount();
public:
	CoinAccount(const int& startingAmount)
	{
		m_balance = KirstenSharedPtr::KirstenSharedPtr(startingAmount);
	}
	int GetBalance() {return *m_balance.Get();};
	void AddBalance(const int& amount);
	void RemoveBalance(const int& amount);
};
#pragma once
#include <memory>

class CoinAccount
{
private:
	int* m_balance;
	CoinAccount();
public:
	CoinAccount(const int& startingAmount)
	{
		m_balance = new int(startingAmount);
	}
	int GetBalance() {return *m_balance;};
	void AddBalance(const int& amount);
	void RemoveBalance(const int& amount);
	void AddBalanceMutex(const int& amount);
	void RemoveBalanceMutex(const int& amount);
};
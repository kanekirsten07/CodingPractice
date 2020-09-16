#pragma once
#include <mutex>
#include <memory>
#include <shared_mutex>

class CoinAccount
{
private:
	int* m_balance;
	//shared lock for read/write purposes
	std::shared_mutex accountMutex;
	CoinAccount();
public:
	CoinAccount(const int& startingAmount)
	{
		std::shared_lock<std::shared_mutex> lock(accountMutex);
		m_balance = new int(startingAmount);
	}
	int GetBalance() {return *m_balance;};
	void AddBalance(const int& amount);
	void RemoveBalance(const int& amount);
	void AddBalanceMutex(const int& amount);
	void RemoveBalanceMutex(const int& amount);
};
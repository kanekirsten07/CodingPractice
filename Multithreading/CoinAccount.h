#pragma once
#include <mutex>
#include <memory>
#include <shared_mutex>

class CoinAccount
{
private:
	int* m_balance;
	std::mutex accountMutex;
	CoinAccount();
public:
	CoinAccount(const int& startingAmount)
	{
		std::lock_guard<std::mutex> guard(accountMutex);
		m_balance = new int(startingAmount);
	}
	int GetBalance() {return *m_balance;};
	void AddBalance(const int& amount);
	void RemoveBalance(const int& amount);
	void AddBalanceMutex(const int& amount);
	void RemoveBalanceMutex(const int& amount);
};
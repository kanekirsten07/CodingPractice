#include "CoinAccount.h"
#include <iostream>

using namespace std;

//The mutex apparently needs to be here and I don't understand things

void CoinAccount::AddBalance(const int& amount)
{
	*m_balance = *m_balance + amount;
}

void CoinAccount::RemoveBalance(const int& amount)
{
	*m_balance = *m_balance - amount;
	if (*m_balance < 0)
	{
		std::cout << "Remove Balance Overdraft!" << "balance:" << *m_balance << endl;
	}
}

void CoinAccount::AddBalanceMutex(const int& amount)
{
	//only one thread should be able to add at a time
	std::lock_guard<std::mutex> guard(accountMutex);
	*m_balance = *m_balance + amount;
}

void CoinAccount::RemoveBalanceMutex(const int& amount)
{
	//only one thread should be able to remove at a time
	std::lock_guard<std::mutex> guard(accountMutex);

	*m_balance = *m_balance - amount;
	if (*m_balance < 0)
	{
		std::cout << "Remove Balance Mutex Overdraft!" << "balance:" << *m_balance << endl;
	}
}



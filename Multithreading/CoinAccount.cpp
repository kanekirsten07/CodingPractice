#include "CoinAccount.h"
#include <iostream>

void CoinAccount::AddBalance(const int& amount)
{
	m_balance.Set(*m_balance.Get() + amount);
}

void CoinAccount::RemoveBalance(const int& amount)
{
	m_balance.Set(*m_balance.Get() + amount);
	if (*m_balance.Get() < 0)
	{
		std::cout << "Overdraft!";
	}
}

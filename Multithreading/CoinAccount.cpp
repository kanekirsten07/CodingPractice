#include "CoinAccount.h"
#include <iostream>
using namespace std;

void CoinAccount::AddBalance(const int& amount)
{
	*m_balance = *m_balance + amount;
}

void CoinAccount::RemoveBalance(const int& amount)
{
	*m_balance = *m_balance - amount;
	if (*m_balance < 0)
	{
		std::cout << "Overdraft!" << endl;
	}
}

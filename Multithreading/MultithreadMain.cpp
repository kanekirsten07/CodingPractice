#include <thread>
#include "CoinAccount.h"
#include <functional>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::placeholders;


void AccountTrade(CoinAccount& account1, CoinAccount& account2, uint32_t account1toAccount2, uint32_t account2toAccount1)
{
	auto addBalanceAccount1 = std::bind(&CoinAccount::AddBalanceMutex, &account1, _1);
	auto removeBalanceAccount1 = std::bind(&CoinAccount::RemoveBalanceMutex, &account1, _1);
	auto addBalanceAccount2 = std::bind(&CoinAccount::AddBalanceMutex, &account2, _1);
	auto removeBalanceAccount2 = std::bind(&CoinAccount::RemoveBalanceMutex, &account2, _1);

	
	std::thread t2(removeBalanceAccount1, account1toAccount2);
	std::thread t4(removeBalanceAccount2, account2toAccount1);
	std::thread t1(addBalanceAccount1, account2toAccount1);
	std::thread t3(addBalanceAccount2, account1toAccount2);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
}

int main()
{
	CoinAccount account(20);

	//Multithreading no mutex
	auto addBalance = std::bind(&CoinAccount::AddBalance, &account, _1);
	auto removeBalance = std::bind(&CoinAccount::RemoveBalance, &account, _1);
	std::cout << "Creating threads. This may overdraft because multithreading reasons. Unless you put a breakpoint and wait" << endl;
	std::thread t1(addBalance,80);
	std::thread t2(removeBalance, 100);
	std::thread t5(addBalance, 20);
	std::thread t6(removeBalance, 20);
	t1.join();
	t2.join();
	t5.join();
	t6.join();
	std::cout << "Account Balance: " << account.GetBalance() << endl;
	
	CoinAccount account2 (20);

	//multithreading with a mutetx
	auto addBalanceMutex = std::bind(&CoinAccount::AddBalanceMutex, &account2, _1);
	auto removeBalanceMutex = std::bind(&CoinAccount::RemoveBalanceMutex, &account2, _1);
	std::cout << "Creating threads. This should not overdraft because lock reasons" << endl;
	std::thread t3(addBalanceMutex, 80);
	std::thread t4(removeBalanceMutex, 100);
	t3.join();
	t4.join();

	if (account2.GetBalance() == 0)
	{
		std::cout << "Success!" << endl;
	}
	else
	{
		std::cout << "Something is wrong" << endl;
	}
	std::cout << "Account Balance: " << account2.GetBalance() << endl;


	//Trading!!
	CoinAccount account3(60);
	CoinAccount account4(20);

	AccountTrade(account3, account4, 40, 20);

	if (account3.GetBalance() == 40)
	{
		std::cout << "Success!" << endl;
	}
	else
	{
		std::cout << "Something is wrong with trade account 1" << endl;
	}

	if (account4.GetBalance() == 40)
	{
		std::cout << "Success!" << endl;
	}
	else
	{
		std::cout << "Something is wrong with trade account 2" << endl;
	}

	std::cout << "Trade Account1 Balance: " << account3.GetBalance() << endl;
	std::cout << "Trade Account2 Balance: " << account4.GetBalance() << endl;

	return 0;
}

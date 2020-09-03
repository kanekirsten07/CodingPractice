#include <thread>
#include "CoinAccount.h"
#include <functional>
#include <thread>
#include <iostream>
using namespace std;
using namespace std::placeholders;

int main()
{
	CoinAccount account = CoinAccount(20);

	//Multithreading no mutex
	auto addBalance = std::bind(&CoinAccount::AddBalance, &account, _1);
	auto removeBalance = std::bind(&CoinAccount::RemoveBalance, &account, _1);
	std::cout << "Creating threads. This will overdraft because multithreading reasons. Unless you put a breakpoint and wait" << endl;
	std::thread t1(addBalance,80);
	std::thread t2(removeBalance, 100);
	std::thread t5(addBalance, 20);
	std::thread t6(removeBalance, 20);
	t1.join();
	t2.join();
	t5.join();
	t6.join();
	std::cout << "Account Balance: " << account.GetBalance() << endl;
	
	CoinAccount account2 = CoinAccount(20);

	//multithreading with a mutetx
	auto addBalanceMutex = std::bind(&CoinAccount::AddBalanceMutex, &account2, _1);
	auto removeBalanceMutex = std::bind(&CoinAccount::RemoveBalanceMutex, &account2, _1);
	std::cout << "Creating threads. This should not because mutex reasons" << endl;
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
	return 0;
}

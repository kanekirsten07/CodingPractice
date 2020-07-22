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

	//Start Thread
	auto addBalance = std::bind(&CoinAccount::AddBalance, &account, _1);
	auto removeBalance = std::bind(&CoinAccount::RemoveBalance, &account, _1);
	std::cout << "Creating threads. This will overdraft because multithreading reasons. Unless you put a breakpoint and wait" << endl;
	std::thread t1(addBalance,80);
	std::thread t2(removeBalance, 100);
	t1.join();
	t2.join();

	std::cout << "Account Balance: " << account.GetBalance() << endl;
	return 0;
}

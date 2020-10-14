#include <thread>
#include "CoinAccount.h"
#include <thread>
#include <iostream>
using namespace std;
using namespace std::placeholders;


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


	//Buying!!
	CoinAccount account3(60);
	CoinAccount account4(20);

	TradeItem* wizardRobes = new TradeItem(TradeItem::ItemType::ROBES, "Sparkly Wizard Robes");

	account4.AddToInventory(wizardRobes);

	std::thread tradeThread([&account3, &account4, &wizardRobes]()
		{
			account3.BuyItem(account4, wizardRobes, 20);
		});

	tradeThread.join();
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

	if (account3.HasItem(wizardRobes))
	{
		std::cout << "Success!" << endl;
	}
	else
	{
		std::cout << "Something is wrong with trade account 1" << endl;
	}

	if (!account4.HasItem(wizardRobes))
	{
		std::cout << "Success!" << endl;
	}
	else
	{
		std::cout << "Something is wrong with trade account 2" << endl;
	}

	std::cout << "Trade Account1 Balance: " << account3.GetBalance() << endl;
	std::cout << "Trade Account2 Balance: " << account4.GetBalance() << endl;

	//Trading!!
	CoinAccount account5(60);
	CoinAccount account6(20);

	TradeItem* shinyWizardRobes = new TradeItem(TradeItem::ItemType::ROBES, "Shiny Wizard Robes");
	TradeItem* sword = new TradeItem(TradeItem::ItemType::SWORD, "Sparkly sword");

	account5.AddToInventory(wizardRobes);
	account6.AddToInventory(sword);

	std::thread tradeThread2([&account5, &account6, &shinyWizardRobes]()
		{
			account5.BuyItem(account6, shinyWizardRobes, 30);
		});

	tradeThread2.join();

	std::thread tradeThread3([&account5, &account6, &sword]()
	{
		account6.BuyItem(account5, sword, 20);
	});

	tradeThread3.join();

	std::cout << "If you dont hit this line, there's probably a deadlock." << endl;
	return 0;
}

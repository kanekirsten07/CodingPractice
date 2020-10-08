#pragma once
#include <mutex>
#include <memory>
#include <functional>
#include <shared_mutex>
#include <vector>
#include "TradeItem.h"

class CoinAccount
{
public:
	CoinAccount(const int& startingAmount)
	{
		std::shared_lock<std::shared_mutex> lock(accountMutex);
		m_balance = new int(startingAmount);
		inventorySize = new int(10);
	}


	int GetBalance() { return *m_balance; };
	bool AddBalance(const int& amount);
	bool RemoveBalance(const int& amount);
	bool AddBalanceMutex(const int& amount);
	bool RemoveBalanceMutex(const int& amount);
	bool HasInventoryRoom();
	bool HasItem(TradeItem* item);
	bool AddToInventory(TradeItem* item);
	bool RemoveItem(TradeItem& tradeItem, /*out*/ TradeItem* item);
	bool AccountTrade(CoinAccount& accountToTrade, TradeItem* item, uint32_t price);
private:
	int* m_balance;
	const int maxBalance = 10000;
	int* inventorySize;
	std::vector<TradeItem *> inventory;
	//shared lock for read/write purposes
	std::shared_mutex accountMutex;
	
	CoinAccount();
};
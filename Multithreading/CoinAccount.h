#pragma once
#include <mutex>
#include <memory>
#include <functional>
#include <vector>
#include "TradeItem.h"

class CoinAccount
{
public:
	CoinAccount(const int& startingAmount)
	{
		m_balance = std::make_shared<int> (startingAmount);
		inventorySize = defaultInventorySize;
	}

	CoinAccount(const int& startingAmount, const int& newInventorySize)
	{
		m_balance = std::make_shared<int>(startingAmount);
		inventorySize = newInventorySize;
	}

	int GetBalance();
	bool AddBalance(const int& amount);
	bool RemoveBalance(const int& amount);
	bool AddBalanceMutex(const int& amount);
	bool RemoveBalanceMutex(const int& amount);
	bool HasInventoryRoom();
	bool HasItem(TradeItem* item);
	bool AddToInventory(TradeItem* item);
	bool RemoveItemFromInventory(TradeItem& tradeItem, /*out*/ TradeItem* item);
	bool BuyItem(CoinAccount& accountToTrade, TradeItem* item, uint32_t price);
private:
	std::shared_ptr<int> m_balance;
	const int maxBalance = 10000;
	const int defaultInventorySize = 10;
	int inventorySize;
	std::vector<TradeItem *> inventory;
	
	CoinAccount();
};
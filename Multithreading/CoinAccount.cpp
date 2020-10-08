#include "CoinAccount.h"
#include <iostream>

using namespace std;

//The mutex apparently needs to be here and I don't understand things

bool CoinAccount::AddBalance(const int& amount)
{
	*m_balance = *m_balance + amount;
	if (*m_balance + amount > maxBalance)
	{
		std::cout << "Over Max Balance of"<< maxBalance << endl;
		return false;
	}
	return true;
}

bool CoinAccount::RemoveBalance(const int& amount)
{
	*m_balance = *m_balance - amount;
	if (*m_balance < 0)
	{
		std::cout << "Remove Balance Overdraft!" << "balance:" << *m_balance << endl;
		return false;
	}
	return true;
}

bool CoinAccount::AddBalanceMutex(const int& amount)
{
	//only one thread should be able to add at a time
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	if (*m_balance + amount > maxBalance)
	{
		std::cout << "Over Max Balance of" << maxBalance << endl;
		return false;
	}
	*m_balance = *m_balance + amount;
	return true;
}

bool CoinAccount::RemoveBalanceMutex(const int& amount)
{
	//only one thread should be able to remove at a time
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	*m_balance = *m_balance - amount;
	if (*m_balance < 0)
	{
		std::cout << "Remove Balance Mutex Overdraft!" << "balance:" << *m_balance << endl;
		return false;
	}
	return true;
}

bool CoinAccount::HasInventoryRoom()
{
	return *inventorySize != inventory.size();
}

bool CoinAccount::HasItem(TradeItem* item)
{
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	for (int i = 0; i < *inventorySize; i++)
	{
		if (inventory[i]->type == item->type && inventory[i]->itemName.compare(item->itemName) == 0)
		{
			return true;
		}
	}
	return false;
}

bool CoinAccount::AddToInventory(TradeItem* item)
{
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	if (!HasInventoryRoom())
	{
		std::cout << "Inventory full!" << endl;
		return false;
	}
	inventory.push_back(item);
	return true;
}

bool CoinAccount::RemoveItem(TradeItem& tradeItem, /*out*/ TradeItem* item)
{
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	for (int i = 0; i < *inventorySize; i++)
	{
		if (inventory[i]->type == tradeItem.type&& inventory[i]->itemName.compare(tradeItem.itemName) == 0)
		{
			item = inventory[i];
			inventory.erase(inventory.begin()+i);
			return true;
		}
	}

	return false;
}

bool CoinAccount::AccountTrade(CoinAccount& accountToTrade, TradeItem* item,uint32_t price)
{
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	if (!HasInventoryRoom())
	{
		std::cout << "Trade failed. Account does not have room to take item." << endl;
		return false;
	}

	if (*m_balance - price < 0)
	{
		std::cout << "Trade failed. Account does not have prerequisite funds." << endl;
		return false;
	}

	if (!RemoveBalanceMutex(price))
	{
		std::cout << "Trade Failed. Remove Balance Failed" << endl;
		return false;
	}

	if (!accountToTrade.AddBalanceMutex(price))
	{
		std::cout << "Trade Failed. Remove Balance Failed" << endl;
		std::cout << "Reverting first account balance";
		if (!AddBalanceMutex(price))
		{
			std::cout << "Remove Balance Revert Failed" << endl;
		}
		return false;
	}
	TradeItem* tradeItem = nullptr;

	if (!accountToTrade.RemoveItem(*item, tradeItem))
	{
		std::cout << "Trade failed, account does not have required item." << endl;
		return false;
	}


	if (!AddToInventory(tradeItem))
	{
		std::cout << "Trade Failed. Cannot Add Item to Inventory" << endl;
		std::cout << "Reverting first account balance";
		if (!AddBalanceMutex(price))
		{
			std::cout << "Remove Balance Revert Failed" << endl;
		}
		else if (!accountToTrade.AddBalanceMutex(price))
		{
			std::cout << "Add Balance Revert Failed" << endl;
		}

		return false;
	}

	return true;
}



#include "CoinAccount.h"
#include <iostream>
#include <shared_mutex>

using namespace std;

//shared lock for read/write purposes
std::shared_mutex accountMutex;
std::recursive_mutex tradeMutex;

int CoinAccount::GetBalance()
{
	std::shared_lock<std::shared_mutex> lock(accountMutex);
	return *m_balance;
};

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
	return inventorySize != inventory.size();
}

bool CoinAccount::HasItem(TradeItem* item)
{
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	for (int i = 0; i < inventory.size(); i++)
	{
		if (nullptr != inventory[i] && inventory[i]->type == item->type && inventory[i]->itemName.compare(item->itemName) == 0)
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

bool CoinAccount::RemoveItemFromInventory(TradeItem& tradeItem, /*out*/ TradeItem* item)
{
	std::unique_lock<std::shared_mutex> lock(accountMutex);
	for (int i = 0; i < inventory.size(); i++)
	{
		if (nullptr != inventory[i] && inventory[i]->type == tradeItem.type&& inventory[i]->itemName.compare(tradeItem.itemName) == 0)
		{
			item = inventory[i];
			inventory.erase(inventory.begin()+i);
			return true;
		}
	}

	return false;
}

bool CoinAccount::BuyItem(CoinAccount& accountToTrade, TradeItem* item,uint32_t price)
{
	std::unique_lock<std::recursive_mutex> lock(tradeMutex);
	//Step 1: check to see if if you have inventory space
	if (!HasInventoryRoom())
	{
		std::cout << "Trade failed. Account does not have room to take item." << endl;
		return false;
	}

	//Step 2: Check to see that the player has the required balance
	if (*m_balance - price < 0)
	{
		std::cout << "Trade failed. Account does not have prerequisite funds." << endl;
		return false;
	}

	//Step 3: Remove balance from buying account
	if (!RemoveBalanceMutex(price))
	{
		std::cout << "Trade Failed. Remove Balance Failed" << endl;
		return false;
	}

	//Step 4: Add balance to selling account
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

	//Step 5: Remove item from selling acccount
	if (!accountToTrade.RemoveItemFromInventory(*item, tradeItem))
	{
		//Revert step 3
		if (!accountToTrade.RemoveBalanceMutex(price))
		{
			std::cout << "Add Balance Revert Failed after attempting to remove item" << endl;
		}

		//Revert step 4
		if (!AddBalanceMutex(price))
		{
			std::cout << "Remove Balance Revert Failed" << endl;
		}
		std::cout << "Trade failed, account does not have required item after attempting to remove item" << endl;
		return false;
	}

	//Step 6: Add Item to buying account's inventory
	if (!AddToInventory(tradeItem))
	{
		std::cout << "Trade Failed. Cannot Add Item to Inventory" << endl;
		std::cout << "Reverting first account balance";

		//Revert step 3
		if (!accountToTrade.AddBalanceMutex(price))
		{
			std::cout << "Add Balance Revert Failed after attempting to add item" << endl;
		}

		//Revert step 4
		if (!AddBalanceMutex(price))
		{
			std::cout << "Remove Balance Revert Failed after attempting to add item" << endl;
		}

		//Revert step 5
		if (!accountToTrade.AddToInventory(item))
		{
			std::cout << "Item readdition failed" << endl;
		}

		return false;
	}

	//Step 6: Success!
	return true;
}



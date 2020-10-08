#pragma once
#include <string>
class TradeItem
{
public:
	enum class ItemType { EMPTY_SLOT, SWORD, SHIELD, HELMET, BOOTS, ROBES, PLATE_ARMOR, STAFF, STONE };
	TradeItem::ItemType type;
	std::string itemName;
	TradeItem(TradeItem::ItemType itemType, std::string name)
		:type(itemType)
		, itemName(name)
	{}
private:
	TradeItem();
};


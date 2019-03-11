#pragma once

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Currency.h"

// Generic inventory for any set of equipment with convenience methods
class CurrencyInventory : public Inventory
{
public:
	template<class T>
	int getCurrencyCount()
	{
		int count = 0;
		std::vector<Item*> items = this->getItems();

		for (auto it = items.begin(); it != items.end(); it++)
		{
			if (dynamic_cast<T*>(*it) != nullptr && dynamic_cast<Currency*>(*it) != nullptr)
			{
				count += (*it)->getCount();
			}
		}

		return count;
	}

protected:
	CurrencyInventory(std::string saveKey = "", int capacity = Inventory::InfiniteCapacity);
	virtual ~CurrencyInventory();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef Inventory super;
};

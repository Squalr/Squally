#pragma once

#include "Engine/SmartNode.h"

class ItemPool;
class Item;
class Inventory;

class ItemChance : public SmartNode
{
public:
	enum class Probability
	{
		Guaranteed,
		VeryCommon,
		Common,
		Uncommon,
		Rare,
		Epic,
		Legendary,
	};

	static ItemChance* create(Item* item, Probability probability);

	Item* getItem();
	float calculateProbability(std::vector<Inventory*> inventories);

protected:
	ItemChance(Item* item, Probability probability);
	~ItemChance();

private:
	typedef SmartNode super;

	Item* item;
	Probability probability;
};

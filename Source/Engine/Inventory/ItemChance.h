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
		// 100%
		Guaranteed,

		// 75%
		VeryCommon,

		// 50%
		Common,

		// 25%
		Reasonable,

		// 15%
		Uncommon,

		// 8%
		Rare,

		// 4%
		Epic,

		// 1%
		Legendary,
	};

	static ItemChance* create(Item* item, Probability probability);
	ItemChance* clone();

	Item* getItem();
	float calculateProbability(std::vector<Inventory*> inventories);
	Probability getProbability();

protected:
	ItemChance(Item* item, Probability probability);
	~ItemChance();

private:
	typedef SmartNode super;

	Item* item;
	Probability probability;
};

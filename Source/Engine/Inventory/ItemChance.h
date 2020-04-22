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
		Guaranteed,	// 100%
		VeryCommon,	// 75%
		Common,		// 50%
		Reasonable,	// 25%
		Uncommon,	// 15%
		Rare,		// 8%
		Epic,		// 4%
		Legendary,	// 2%
		Artifact,	// 1%
	};

	static ItemChance* create(Item* item, Probability probability);
	ItemChance* clone();

	Item* getItem();
	float calculateProbability(std::vector<Inventory*> inventories);
	Probability getProbability();

protected:
	ItemChance(Item* item, Probability probability);
	virtual ~ItemChance();

private:
	typedef SmartNode super;

	Item* item;
	Probability probability;
};

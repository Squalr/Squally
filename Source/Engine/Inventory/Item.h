#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Value;
	typedef std::map<std::string, Value> ValueMap;
}

class CurrencyInventory;
class LocalizedString;

class Item : public SmartNode
{
public:
	virtual Item* clone() = 0;
	virtual std::string getItemName() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getIconResource() = 0;
	virtual std::string getSerializationKey() = 0;
	CurrencyInventory* getCost();
	int getUniqueCount();
	int getRubberBand();
	float getRubberBandFactor();

	struct ItemMeta
	{
		// The "expected value" that the player should have
		int rubberBand;

		// Standard deviation to place around
		float rubberBandFactor;
		
		// How many of this item can exist in inventories.
		int unique;

		ItemMeta(int rubberBand, float rubberBandFactor, int unique) : rubberBand(rubberBand), rubberBandFactor(rubberBandFactor), unique(unique) { }
		ItemMeta(int rubberBand, float rubberBandFactor) : rubberBand(rubberBand), rubberBandFactor(rubberBandFactor), unique(-1) { }
		ItemMeta(int unique) : rubberBand(-1), rubberBandFactor(0.0f), unique(unique) { }
		ItemMeta() : rubberBand(-1), rubberBandFactor(0.0f), unique(-1) { }
	};

protected:
	Item(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	virtual ~Item();
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	ItemMeta itemMeta;
	CurrencyInventory* cost;
};

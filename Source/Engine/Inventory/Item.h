#pragma once

#include "cocos/base/CCValue.h"
#include "Engine/SmartNode.h"

class CurrencyInventory;
class LocalizedString;

class Item : public SmartNode
{
public:
	struct RubberBanding
	{
		// The "expected value" that the player should have
		int rubberBand;

		// Standard deviation to place around
		float rubberBandFactor;

		RubberBanding() : rubberBand(-1), rubberBandFactor(0.0f) { }
		RubberBanding(int rubberBand, float rubberBandFactor) : rubberBand(rubberBand), rubberBandFactor(rubberBandFactor) { }
	};

	struct ItemMeta
	{
		// How many of this item can exist in a stack;
		int stackSize;

		// How many of this item can exist in inventories.
		int unique;

		RubberBanding rubberBanding;

		ItemMeta(int stackSize) : stackSize(stackSize), rubberBanding(RubberBanding()) { }
		ItemMeta(int stackSize, int unique) : stackSize(stackSize), unique(unique), rubberBanding(RubberBanding()) { }
		ItemMeta(int stackSize, int unique, RubberBanding rubberBanding) : stackSize(stackSize), unique(unique), rubberBanding(rubberBanding) { }
		ItemMeta(int stackSize, RubberBanding rubberBanding) : stackSize(stackSize), unique(-1), rubberBanding(rubberBanding) { }
		ItemMeta(RubberBanding rubberBanding) : stackSize(1), unique(-1), rubberBanding(rubberBanding) { }
		ItemMeta() : stackSize(1), unique(-1), rubberBanding(RubberBanding()) { }
	};

	virtual Item* clone() = 0;
	virtual std::string getItemName() = 0;
	virtual LocalizedString* getString() = 0;
	virtual std::string getIconResource() = 0;
	virtual std::string getSerializationKey() = 0;
	CurrencyInventory* getCost();
	int getStackSize();
	int getUniqueCount();
	int getRubberBand();
	float getRubberBandFactor();

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

#pragma once

#include "cocos/base/CCValue.h"
#include "Engine/SmartNode.h"

class CurrencyInventory;
class LocalizedString;
class Recipe;

class Item : public SmartNode
{
public:
	struct RubberBanding
	{
		// The "expected value" that the player should have
		int rubberBand = -1;

		// Standard deviation to place around
		float rubberBandFactor = 0.0f;

		RubberBanding(int rubberBand, float rubberBandFactor) : rubberBand(rubberBand), rubberBandFactor(rubberBandFactor) { }
		RubberBanding() { }
	};

	struct ItemMeta
	{
		// How many of this item can exist in a stack;
		int stackSize = 1;

		// How many of this item can exist in inventories.
		int unique = -1;

		RubberBanding rubberBanding;
		
		ItemMeta(int stackSize, int unique = -1, RubberBanding rubberBanding = RubberBanding()) : stackSize(stackSize), unique(unique), rubberBanding(rubberBanding) { }
		ItemMeta(int stackSize, RubberBanding rubberBanding) : stackSize(stackSize), rubberBanding(rubberBanding) { }
		ItemMeta(RubberBanding rubberBanding) : rubberBanding(rubberBanding) { }
		ItemMeta() { }
	};

	virtual Item* clone() = 0;
	virtual LocalizedString* getString() = 0;
	virtual const std::string& getIconResource() = 0;
	virtual const std::string& getIdentifier() = 0;
	virtual Recipe* getRecipe() { return nullptr; };
	CurrencyInventory* getCost();
	int getStackSize();
	int getUniqueCount();
	int getRubberBand();
	float getRubberBandFactor();

protected:
	Item(CurrencyInventory* cost = nullptr, ItemMeta itemMeta = ItemMeta());
	virtual ~Item();
	
	void onEnter() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	ItemMeta itemMeta;
	CurrencyInventory* cost = nullptr;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class SwordRecipe : public Recipe
{
public:
protected:
	SwordRecipe(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	virtual ~SwordRecipe();

private:
	typedef Recipe super;
};

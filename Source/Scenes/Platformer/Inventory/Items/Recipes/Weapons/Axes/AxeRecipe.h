#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class AxeRecipe : public Recipe
{
public:
protected:
	AxeRecipe(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	virtual ~AxeRecipe();

private:
	typedef Recipe super;
};

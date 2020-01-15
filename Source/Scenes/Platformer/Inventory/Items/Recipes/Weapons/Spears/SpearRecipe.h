#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class SpearRecipe : public Recipe
{
public:
protected:
	SpearRecipe(CurrencyInventory* cost, ItemMeta itemMeta = ItemMeta());
	virtual ~SpearRecipe();

private:
	typedef Recipe super;
};

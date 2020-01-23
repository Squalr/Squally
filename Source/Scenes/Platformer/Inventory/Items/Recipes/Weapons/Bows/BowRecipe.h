#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class BowRecipe : public Recipe
{
public:
protected:
	BowRecipe(CurrencyInventory* cost);
	virtual ~BowRecipe();

private:
	typedef Recipe super;
};

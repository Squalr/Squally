#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class TransmuteRecipe : public Recipe
{
public:
protected:
	TransmuteRecipe(CurrencyInventory* cost);
	virtual ~TransmuteRecipe();

private:
	typedef Recipe super;
};

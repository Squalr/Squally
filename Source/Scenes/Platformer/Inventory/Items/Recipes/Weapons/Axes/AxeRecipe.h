#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class AxeRecipe : public Recipe
{
public:
protected:
	AxeRecipe(CurrencyInventory* cost);
	virtual ~AxeRecipe();

private:
	typedef Recipe super;
};

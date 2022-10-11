#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class HatRecipe : public Recipe
{
public:
protected:
	HatRecipe(CurrencyInventory* cost);
	virtual ~HatRecipe();

private:
	typedef Recipe super;
};

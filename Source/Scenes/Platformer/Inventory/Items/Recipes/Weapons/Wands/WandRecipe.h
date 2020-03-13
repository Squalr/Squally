#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class WandRecipe : public Recipe
{
public:
protected:
	WandRecipe(CurrencyInventory* cost);
	virtual ~WandRecipe();

private:
	typedef Recipe super;
};

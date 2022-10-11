#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class NecklaceRecipe : public Recipe
{
public:
protected:
	NecklaceRecipe(CurrencyInventory* cost);
	virtual ~NecklaceRecipe();

private:
	typedef Recipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class RingRecipe : public Recipe
{
public:
protected:
	RingRecipe(CurrencyInventory* cost);
	virtual ~RingRecipe();

private:
	typedef Recipe super;
};

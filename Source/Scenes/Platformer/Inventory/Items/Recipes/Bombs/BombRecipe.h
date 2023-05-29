#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class BombRecipe : public Recipe
{
public:
protected:
	BombRecipe(CurrencyInventory* cost);
	virtual ~BombRecipe();

private:
	typedef Recipe super;
};

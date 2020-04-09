#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class PotionRecipe : public Recipe
{
public:
protected:
	PotionRecipe(CurrencyInventory* cost);
	virtual ~PotionRecipe();

private:
	typedef Recipe super;
};

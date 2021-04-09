#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class EarringsRecipe : public Recipe
{
public:
protected:
	EarringsRecipe(CurrencyInventory* cost);
	virtual ~EarringsRecipe();

private:
	typedef Recipe super;
};

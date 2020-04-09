#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class MaceRecipe : public Recipe
{
public:
protected:
	MaceRecipe(CurrencyInventory* cost);
	virtual ~MaceRecipe();

private:
	typedef Recipe super;
};

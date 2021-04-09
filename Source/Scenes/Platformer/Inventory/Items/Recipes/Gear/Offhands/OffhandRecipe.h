#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class OffhandRecipe : public Recipe
{
public:
protected:
	OffhandRecipe(CurrencyInventory* cost);
	virtual ~OffhandRecipe();

private:
	typedef Recipe super;
};

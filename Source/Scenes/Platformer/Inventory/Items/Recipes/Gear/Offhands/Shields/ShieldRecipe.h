#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Offhands/OffhandRecipe.h"

class ShieldRecipe : public OffhandRecipe
{
public:
protected:
	ShieldRecipe(CurrencyInventory* cost);
	virtual ~ShieldRecipe();

private:
	typedef OffhandRecipe super;
};

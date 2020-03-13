#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"

class CursedWandPlans : public WandRecipe
{
public:
	static CursedWandPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCursedWandPlans;

protected:
	CursedWandPlans();
	virtual ~CursedWandPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef WandRecipe super;
};

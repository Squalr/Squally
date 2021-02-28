#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"

class QuartzWandPlans : public WandRecipe
{
public:
	static QuartzWandPlans* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	QuartzWandPlans();
	virtual ~QuartzWandPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef WandRecipe super;
};

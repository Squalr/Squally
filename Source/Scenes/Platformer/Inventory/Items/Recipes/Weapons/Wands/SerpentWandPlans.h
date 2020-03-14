#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"

class SerpentWandPlans : public WandRecipe
{
public:
	static SerpentWandPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySerpentWandPlans;

protected:
	SerpentWandPlans();
	virtual ~SerpentWandPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef WandRecipe super;
};

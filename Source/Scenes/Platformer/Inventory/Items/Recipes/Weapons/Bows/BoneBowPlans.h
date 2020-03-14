#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"

class BoneBowPlans : public BowRecipe
{
public:
	static BoneBowPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBoneBowPlans;

protected:
	BoneBowPlans();
	virtual ~BoneBowPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef BowRecipe super;
};

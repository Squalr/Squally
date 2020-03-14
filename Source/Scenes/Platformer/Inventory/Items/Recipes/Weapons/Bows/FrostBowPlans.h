#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"

class FrostBowPlans : public BowRecipe
{
public:
	static FrostBowPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyFrostBowPlans;

protected:
	FrostBowPlans();
	virtual ~FrostBowPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef BowRecipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"

class CompositeBowPlans : public BowRecipe
{
public:
	static CompositeBowPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyCompositeBowPlans;

protected:
	CompositeBowPlans();
	virtual ~CompositeBowPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef BowRecipe super;
};

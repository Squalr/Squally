#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"

class ImpalerPlans : public BowRecipe
{
public:
	static ImpalerPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyImpalerPlans;

protected:
	ImpalerPlans();
	virtual ~ImpalerPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef BowRecipe super;
};

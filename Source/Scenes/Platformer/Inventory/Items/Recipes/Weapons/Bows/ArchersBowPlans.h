#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"

class ArchersBowPlans : public BowRecipe
{
public:
	static ArchersBowPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyArchersBowPlans;

protected:
	ArchersBowPlans();
	virtual ~ArchersBowPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef BowRecipe super;
};

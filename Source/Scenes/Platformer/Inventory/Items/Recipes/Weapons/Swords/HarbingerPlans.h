#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"

class HarbingerPlans : public SwordRecipe
{
public:
	static HarbingerPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHarbingerPlans;

protected:
	HarbingerPlans();
	virtual ~HarbingerPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef SwordRecipe super;
};

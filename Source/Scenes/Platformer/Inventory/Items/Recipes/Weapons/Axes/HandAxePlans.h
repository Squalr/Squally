#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/AxeRecipe.h"

class HandAxePlans : public AxeRecipe
{
public:
	static HandAxePlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHandAxePlans;

protected:
	HandAxePlans();
	virtual ~HandAxePlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef AxeRecipe super;
};

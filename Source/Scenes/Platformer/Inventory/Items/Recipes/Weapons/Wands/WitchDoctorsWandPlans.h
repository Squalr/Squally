#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"

class WitchDoctorsWandPlans : public WandRecipe
{
public:
	static WitchDoctorsWandPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyWitchDoctorsWandPlans;

protected:
	WitchDoctorsWandPlans();
	virtual ~WitchDoctorsWandPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef WandRecipe super;
};

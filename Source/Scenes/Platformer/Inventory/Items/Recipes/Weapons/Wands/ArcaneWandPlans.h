#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"

class ArcaneWandPlans : public WandRecipe
{
public:
	static ArcaneWandPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyArcaneWandPlans;

protected:
	ArcaneWandPlans();
	virtual ~ArcaneWandPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef WandRecipe super;
};

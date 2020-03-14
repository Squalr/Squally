#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/AxeRecipe.h"

class HedgeTrimmerPlans : public AxeRecipe
{
public:
	static HedgeTrimmerPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHedgeTrimmerPlans;

protected:
	HedgeTrimmerPlans();
	virtual ~HedgeTrimmerPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef AxeRecipe super;
};

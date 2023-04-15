#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class HellCrystalPlans : public Recipe
{
public:
	static HellCrystalPlans* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	HellCrystalPlans();
	virtual ~HellCrystalPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef Recipe super;
};

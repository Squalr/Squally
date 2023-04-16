#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class DemonHeartPlans : public Recipe
{
public:
	static DemonHeartPlans* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	DemonHeartPlans();
	virtual ~DemonHeartPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef Recipe super;
};

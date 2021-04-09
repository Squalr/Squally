#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/HatRecipe.h"

class PriestHatPlans : public HatRecipe
{
public:
	static PriestHatPlans* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	PriestHatPlans();
	virtual ~PriestHatPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef HatRecipe super;
};

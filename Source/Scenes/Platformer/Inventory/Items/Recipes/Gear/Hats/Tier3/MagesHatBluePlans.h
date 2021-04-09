#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Hats/HatRecipe.h"

class MagesHatBluePlans : public HatRecipe
{
public:
	static MagesHatBluePlans* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	MagesHatBluePlans();
	virtual ~MagesHatBluePlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef HatRecipe super;
};

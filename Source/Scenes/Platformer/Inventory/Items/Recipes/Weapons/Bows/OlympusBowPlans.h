#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Bows/BowRecipe.h"

class OlympusBowPlans : public BowRecipe
{
public:
	static OlympusBowPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyOlympusBowPlans;

protected:
	OlympusBowPlans();
	virtual ~OlympusBowPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef BowRecipe super;
};

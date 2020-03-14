#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"

class MoonBladePlans : public SwordRecipe
{
public:
	static MoonBladePlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyMoonBladePlans;

protected:
	MoonBladePlans();
	virtual ~MoonBladePlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef SwordRecipe super;
};

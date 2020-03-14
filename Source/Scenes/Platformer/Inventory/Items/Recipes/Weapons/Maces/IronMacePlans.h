#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MaceRecipe.h"

class IronMacePlans : public MaceRecipe
{
public:
	static IronMacePlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyIronMacePlans;

protected:
	IronMacePlans();
	virtual ~IronMacePlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef MaceRecipe super;
};

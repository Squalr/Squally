#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MaceRecipe.h"

class SpikedClubPlans : public MaceRecipe
{
public:
	static SpikedClubPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeySpikedClubPlans;

protected:
	SpikedClubPlans();
	virtual ~SpikedClubPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef MaceRecipe super;
};

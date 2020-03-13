#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MaceRecipe.h"

class BattleHammerPlans : public MaceRecipe
{
public:
	static BattleHammerPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBattleHammerPlans;

protected:
	BattleHammerPlans();
	virtual ~BattleHammerPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef MaceRecipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/AxeRecipe.h"

class BattleAxePlans : public AxeRecipe
{
public:
	static BattleAxePlans* create();

	Item* craft() override;
	std::map<std::string, int> getReagents() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBattleAxePlans;

protected:
	BattleAxePlans();
	virtual ~BattleAxePlans();

private:
	typedef AxeRecipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"

class CrystalSwordPlans : public SwordRecipe
{
public:
	static CrystalSwordPlans* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	CrystalSwordPlans();
	virtual ~CrystalSwordPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef SwordRecipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"

class IronSwordPlans : public SwordRecipe
{
public:
	static IronSwordPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyIronSwordPlans;

protected:
	IronSwordPlans();
	virtual ~IronSwordPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef SwordRecipe super;
};

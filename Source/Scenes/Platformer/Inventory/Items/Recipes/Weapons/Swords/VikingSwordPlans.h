#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Swords/SwordRecipe.h"

class VikingSwordPlans : public SwordRecipe
{
public:
	static VikingSwordPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyVikingSwordPlans;

protected:
	VikingSwordPlans();
	virtual ~VikingSwordPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef SwordRecipe super;
};

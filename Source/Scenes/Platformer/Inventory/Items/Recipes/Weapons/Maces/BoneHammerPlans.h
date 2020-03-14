#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Maces/MaceRecipe.h"

class BoneHammerPlans : public MaceRecipe
{
public:
	static BoneHammerPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBoneHammerPlans;

protected:
	BoneHammerPlans();
	virtual ~BoneHammerPlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef MaceRecipe super;
};

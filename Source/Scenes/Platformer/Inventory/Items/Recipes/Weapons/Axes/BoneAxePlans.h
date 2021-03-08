#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Axes/AxeRecipe.h"

class BoneAxePlans : public AxeRecipe
{
public:
	static BoneAxePlans* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	BoneAxePlans();
	virtual ~BoneAxePlans();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef AxeRecipe super;
};

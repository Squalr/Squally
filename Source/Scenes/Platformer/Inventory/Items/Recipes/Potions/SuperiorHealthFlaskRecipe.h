#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Potions/PotionRecipe.h"

class SuperiorHealthFlaskRecipe : public PotionRecipe
{
public:
	static SuperiorHealthFlaskRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	SuperiorHealthFlaskRecipe();
	virtual ~SuperiorHealthFlaskRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef PotionRecipe super;
};

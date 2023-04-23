#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteRecipe.h"

class LargeBombRecipe : public TransmuteRecipe
{
public:
	static LargeBombRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	LargeBombRecipe();
	virtual ~LargeBombRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef TransmuteRecipe super;
};

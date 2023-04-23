#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteRecipe.h"

class SpikedBombRecipe : public TransmuteRecipe
{
public:
	static SpikedBombRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	SpikedBombRecipe();
	virtual ~SpikedBombRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef TransmuteRecipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Transmutes/TransmuteRecipe.h"

class TransmuteQuartzToEmerald : public TransmuteRecipe
{
public:
	static TransmuteQuartzToEmerald* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	TransmuteQuartzToEmerald();
	virtual ~TransmuteQuartzToEmerald();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef TransmuteRecipe super;
};

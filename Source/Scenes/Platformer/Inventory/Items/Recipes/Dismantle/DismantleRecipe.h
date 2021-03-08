#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class DismantleRecipe : public Recipe
{
public:
	static DismantleRecipe* create(Item* item);

	std::vector<Item*> craft() override;
	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string ItemNamePrefix;

protected:
	DismantleRecipe(Item* item);
	virtual ~DismantleRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef Recipe super;

	Item* dismantleItem;
	Recipe* dismantledItemRecipe;
	std::string dismantleItemName;
};

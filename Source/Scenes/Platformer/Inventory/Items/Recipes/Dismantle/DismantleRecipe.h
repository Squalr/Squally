#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"

class DismantleRecipe : public Recipe
{
public:
	static DismantleRecipe* create(Item* item);

	std::vector<Item*> craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	DismantleRecipe(Item* item);
	virtual ~DismantleRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef Recipe super;

	Item* dismantleItem;
	Recipe* dismantledItemRecipe;
};

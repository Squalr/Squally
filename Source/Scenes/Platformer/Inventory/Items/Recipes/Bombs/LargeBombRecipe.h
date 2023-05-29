#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/BombRecipe.h"

class LargeBombRecipe : public BombRecipe
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
	typedef BombRecipe super;
};

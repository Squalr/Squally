#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/BombRecipe.h"

class SteelBombRecipe : public BombRecipe
{
public:
	static SteelBombRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	SteelBombRecipe();
	virtual ~SteelBombRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef BombRecipe super;
};

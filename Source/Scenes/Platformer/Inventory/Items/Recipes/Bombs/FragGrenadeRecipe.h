#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/BombRecipe.h"

class FragGrenadeRecipe : public BombRecipe
{
public:
	static FragGrenadeRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	FragGrenadeRecipe();
	virtual ~FragGrenadeRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef BombRecipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Bombs/BombRecipe.h"

class SpikedBombRecipe : public BombRecipe
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
	typedef BombRecipe super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Rings/RingRecipe.h"

class ShellBandRecipe : public RingRecipe
{
public:
	static ShellBandRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	ShellBandRecipe();
	virtual ~ShellBandRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef RingRecipe super;
};

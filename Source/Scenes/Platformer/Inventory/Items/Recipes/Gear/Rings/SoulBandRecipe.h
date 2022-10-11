#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Rings/RingRecipe.h"

class SoulBandRecipe : public RingRecipe
{
public:
	static SoulBandRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	SoulBandRecipe();
	virtual ~SoulBandRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef RingRecipe super;
};

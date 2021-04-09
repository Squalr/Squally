#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Earrings/EarringsRecipe.h"

class CrystalEarringsRecipe : public EarringsRecipe
{
public:
	static CrystalEarringsRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	CrystalEarringsRecipe();
	virtual ~CrystalEarringsRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef EarringsRecipe super;
};

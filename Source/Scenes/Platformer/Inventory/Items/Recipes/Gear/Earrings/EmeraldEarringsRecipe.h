#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Gear/Earrings/EarringsRecipe.h"

class EmeraldEarringsRecipe : public EarringsRecipe
{
public:
	static EmeraldEarringsRecipe* create();

	std::vector<Item*> craft() override;
	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	std::string getCraftedItemIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	EmeraldEarringsRecipe();
	virtual ~EmeraldEarringsRecipe();
	
	std::vector<std::tuple<Item*, int>> getReagentsInternal() override;

private:
	typedef EarringsRecipe super;
};

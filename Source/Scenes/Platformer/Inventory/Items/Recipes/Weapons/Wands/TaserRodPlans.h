#pragma once

#include "Scenes/Platformer/Inventory/Items/Recipes/Weapons/Wands/WandRecipe.h"

class TaserRodPlans : public WandRecipe
{
public:
	static TaserRodPlans* create();

	Item* craft() override;
	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getCraftedItemIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyTaserRodPlans;

protected:
	TaserRodPlans();
	virtual ~TaserRodPlans();
	
	std::map<Item*, int> getReagentsInternal() override;

private:
	typedef WandRecipe super;
};

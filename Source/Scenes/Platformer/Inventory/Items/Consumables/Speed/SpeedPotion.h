#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class SpeedPotion : public Consumable
{
public:
	static SpeedPotion* create();

	Item* clone() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	ConsumableType getConsumableType() override;

	static const std::string SaveKeySpeedPotion;

protected:
	SpeedPotion();
	virtual ~SpeedPotion();

private:
	typedef Consumable super;
};

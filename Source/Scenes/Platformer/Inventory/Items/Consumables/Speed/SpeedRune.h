#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class SpeedRune : public Consumable
{
public:
	static SpeedRune* create();

	Item* clone() override;
	PlatformerAttack* createAssociatedAttack() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	ConsumableType getConsumableType() override;

	static const std::string SaveKeySpeedRune;

protected:
	SpeedRune();
	virtual ~SpeedRune();

private:
	typedef Consumable super;
};

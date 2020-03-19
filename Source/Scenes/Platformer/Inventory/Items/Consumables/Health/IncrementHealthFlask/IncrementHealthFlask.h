#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class IncrementHealthFlask : public Consumable
{
public:
	static IncrementHealthFlask* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;
	static const int HealTicks;

protected:
	IncrementHealthFlask();
	virtual ~IncrementHealthFlask();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};

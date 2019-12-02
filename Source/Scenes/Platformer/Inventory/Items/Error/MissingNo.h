#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class MissingNo : public Consumable
{
public:
	static MissingNo* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyMissingNo;

protected:
	MissingNo();
	~MissingNo();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};

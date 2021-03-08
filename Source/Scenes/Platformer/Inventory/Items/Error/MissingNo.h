#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class MissingNo : public Consumable
{
public:
	static MissingNo* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;

	static const std::string SaveKey;

protected:
	MissingNo();
	~MissingNo();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"

class LocalizedString;

class MissingNo : public Consumable
{
public:
	static MissingNo* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	MissingNo();
	virtual ~MissingNo();

	PlatformerAttack* createAssociatedAttack() override;

private:
	typedef Consumable super;
};

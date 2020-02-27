#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/Sword.h"

class FangBlade : public Sword
{
public:
	static FangBlade* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyFangBlade;

protected:
	FangBlade();
	virtual ~FangBlade();

private:
	typedef Sword super;
};

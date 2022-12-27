#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class HellGateCrystal : public Key
{
public:
	static HellGateCrystal* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	HellGateCrystal();
	virtual ~HellGateCrystal();

private:
	typedef Key super;
};

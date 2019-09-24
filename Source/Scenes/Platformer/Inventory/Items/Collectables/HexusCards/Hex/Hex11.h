#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Hex11 : public HexusCard
{
public:
	static Hex11* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHex11;

protected:
	Hex11();
	~Hex11();

private:
	typedef HexusCard super;
};

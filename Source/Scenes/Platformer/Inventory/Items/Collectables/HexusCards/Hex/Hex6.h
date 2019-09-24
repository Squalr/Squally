#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Hex6 : public HexusCard
{
public:
	static Hex6* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHex6;

protected:
	Hex6();
	~Hex6();

private:
	typedef HexusCard super;
};

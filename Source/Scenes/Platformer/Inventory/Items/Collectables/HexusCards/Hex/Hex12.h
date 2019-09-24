#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Hex12 : public HexusCard
{
public:
	static Hex12* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyHex12;

protected:
	Hex12();
	~Hex12();

private:
	typedef HexusCard super;
};

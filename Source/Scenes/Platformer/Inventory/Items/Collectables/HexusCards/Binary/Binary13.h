#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary13 : public HexusCard
{
public:
	static Binary13* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBinary13;

protected:
	Binary13();
	~Binary13();

private:
	typedef HexusCard super;
};

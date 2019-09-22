#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary1 : public HexusCard
{
public:
	static Binary1* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBinary1;

protected:
	Binary1();
	~Binary1();

private:
	typedef HexusCard super;
};

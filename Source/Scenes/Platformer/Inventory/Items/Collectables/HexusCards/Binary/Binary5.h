#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary5 : public HexusCard
{
public:
	static Binary5* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBinary5;

protected:
	Binary5();
	~Binary5();

private:
	typedef HexusCard super;
};

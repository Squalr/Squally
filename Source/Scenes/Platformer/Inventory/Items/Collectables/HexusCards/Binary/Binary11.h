#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary11 : public HexusCard
{
public:
	static Binary11* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyBinary11;

protected:
	Binary11();
	~Binary11();

private:
	typedef HexusCard super;
};

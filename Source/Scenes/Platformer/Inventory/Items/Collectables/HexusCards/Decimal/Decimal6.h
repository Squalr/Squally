#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal6 : public HexusCard
{
public:
	static Decimal6* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeyDecimal6;

protected:
	Decimal6();
	~Decimal6();

private:
	typedef HexusCard super;
};

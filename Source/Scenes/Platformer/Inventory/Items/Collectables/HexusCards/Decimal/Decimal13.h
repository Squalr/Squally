#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal13 : public HexusCard
{
public:
	static Decimal13* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeyDecimal13;

protected:
	Decimal13();
	~Decimal13();

private:
	typedef HexusCard super;
};

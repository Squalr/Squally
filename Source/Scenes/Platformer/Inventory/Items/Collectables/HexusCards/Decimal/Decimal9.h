#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal9 : public HexusCard
{
public:
	static Decimal9* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeyDecimal9;

protected:
	Decimal9();
	~Decimal9();

private:
	typedef HexusCard super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal15 : public HexusCard
{
public:
	static Decimal15* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeyDecimal15;

protected:
	Decimal15();
	~Decimal15();

private:
	typedef HexusCard super;
};

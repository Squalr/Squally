#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal10 : public HexusCard
{
public:
	static Decimal10* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDecimal10;

protected:
	Decimal10();
	~Decimal10();

private:
	typedef HexusCard super;
};

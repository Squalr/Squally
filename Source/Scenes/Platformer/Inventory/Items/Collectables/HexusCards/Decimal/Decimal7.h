#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal7 : public HexusCard
{
public:
	static Decimal7* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDecimal7;

protected:
	Decimal7();
	~Decimal7();

private:
	typedef HexusCard super;
};

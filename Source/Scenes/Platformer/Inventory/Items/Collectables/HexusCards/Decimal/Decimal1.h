#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal1 : public HexusCard
{
public:
	static Decimal1* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDecimal1;

protected:
	Decimal1();
	~Decimal1();

private:
	typedef HexusCard super;
};

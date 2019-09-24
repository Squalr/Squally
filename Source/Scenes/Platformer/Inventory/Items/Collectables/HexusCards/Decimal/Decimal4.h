#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal4 : public HexusCard
{
public:
	static Decimal4* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDecimal4;

protected:
	Decimal4();
	~Decimal4();

private:
	typedef HexusCard super;
};

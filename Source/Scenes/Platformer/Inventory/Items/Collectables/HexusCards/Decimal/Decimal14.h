#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal14 : public HexusCard
{
public:
	static Decimal14* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDecimal14;

protected:
	Decimal14();
	~Decimal14();

private:
	typedef HexusCard super;
};

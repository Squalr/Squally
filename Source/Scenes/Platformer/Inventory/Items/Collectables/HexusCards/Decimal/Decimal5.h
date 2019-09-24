#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal5 : public HexusCard
{
public:
	static Decimal5* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDecimal5;

protected:
	Decimal5();
	~Decimal5();

private:
	typedef HexusCard super;
};

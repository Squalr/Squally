#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal8 : public HexusCard
{
public:
	static Decimal8* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKeyDecimal8;

protected:
	Decimal8();
	~Decimal8();

private:
	typedef HexusCard super;
};

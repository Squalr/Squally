#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal0 : public HexusCard
{
public:
	static Decimal0* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	Decimal0();
	~Decimal0();

private:
	typedef HexusCard super;
};

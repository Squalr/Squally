#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Decimal5 : public HexusCard
{
public:
	static Decimal5* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	Decimal5();
	virtual ~Decimal5();

private:
	typedef HexusCard super;
};

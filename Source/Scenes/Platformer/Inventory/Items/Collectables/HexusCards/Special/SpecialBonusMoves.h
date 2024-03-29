#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialBonusMoves : public HexusCard
{
public:
	static SpecialBonusMoves* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialBonusMoves();
	virtual ~SpecialBonusMoves();

private:
	typedef HexusCard super;
};

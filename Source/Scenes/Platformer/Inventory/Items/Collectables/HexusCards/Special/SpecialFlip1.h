#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialFlip1 : public HexusCard
{
public:
	static SpecialFlip1* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialFlip1();
	virtual ~SpecialFlip1();

private:
	typedef HexusCard super;
};

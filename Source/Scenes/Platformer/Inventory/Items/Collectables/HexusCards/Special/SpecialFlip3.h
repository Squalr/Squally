#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialFlip3 : public HexusCard
{
public:
	static SpecialFlip3* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialFlip3();
	virtual ~SpecialFlip3();

private:
	typedef HexusCard super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialFlip3 : public HexusCard
{
public:
	static SpecialFlip3* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeySpecialFlip3;

protected:
	SpecialFlip3();
	~SpecialFlip3();

private:
	typedef HexusCard super;
};

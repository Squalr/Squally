#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialFlip1 : public HexusCard
{
public:
	static SpecialFlip1* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeySpecialFlip1;

protected:
	SpecialFlip1();
	~SpecialFlip1();

private:
	typedef HexusCard super;
};

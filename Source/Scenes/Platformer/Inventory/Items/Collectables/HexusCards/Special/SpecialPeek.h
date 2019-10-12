#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialPeek : public HexusCard
{
public:
	static SpecialPeek* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeySpecialPeek;

protected:
	SpecialPeek();
	~SpecialPeek();

private:
	typedef HexusCard super;
};

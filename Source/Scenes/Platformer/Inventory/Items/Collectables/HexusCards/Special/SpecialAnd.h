#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialAnd : public HexusCard
{
public:
	static SpecialAnd* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeySpecialAnd;

protected:
	SpecialAnd();
	~SpecialAnd();

private:
	typedef HexusCard super;
};

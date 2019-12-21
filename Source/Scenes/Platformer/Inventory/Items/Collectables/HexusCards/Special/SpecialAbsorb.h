#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialAbsorb : public HexusCard
{
public:
	static SpecialAbsorb* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeySpecialAbsorb;

protected:
	SpecialAbsorb();
	~SpecialAbsorb();

private:
	typedef HexusCard super;
};

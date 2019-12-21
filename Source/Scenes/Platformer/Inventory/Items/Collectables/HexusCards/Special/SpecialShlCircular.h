#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialShlCircular : public HexusCard
{
public:
	static SpecialShlCircular* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeySpecialShlCircular;

protected:
	SpecialShlCircular();
	~SpecialShlCircular();

private:
	typedef HexusCard super;
};

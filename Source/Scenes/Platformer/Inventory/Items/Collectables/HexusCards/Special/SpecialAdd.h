#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialAdd : public HexusCard
{
public:
	static SpecialAdd* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKeySpecialAdd;

protected:
	SpecialAdd();
	~SpecialAdd();

private:
	typedef HexusCard super;
};

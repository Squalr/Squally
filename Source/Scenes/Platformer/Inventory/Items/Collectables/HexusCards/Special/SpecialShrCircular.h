#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialShrCircular : public HexusCard
{
public:
	static SpecialShrCircular* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialShrCircular();
	~SpecialShrCircular();

private:
	typedef HexusCard super;
};

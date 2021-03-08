#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialShlCircular : public HexusCard
{
public:
	static SpecialShlCircular* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialShlCircular();
	virtual ~SpecialShlCircular();

private:
	typedef HexusCard super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialShl : public HexusCard
{
public:
	static SpecialShl* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialShl();
	virtual ~SpecialShl();

private:
	typedef HexusCard super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialOr : public HexusCard
{
public:
	static SpecialOr* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialOr();
	virtual ~SpecialOr();

private:
	typedef HexusCard super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialPeek : public HexusCard
{
public:
	static SpecialPeek* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialPeek();
	virtual ~SpecialPeek();

private:
	typedef HexusCard super;
};

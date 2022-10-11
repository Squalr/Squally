#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary1 : public HexusCard
{
public:
	static Binary1* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	Binary1();
	virtual ~Binary1();

private:
	typedef HexusCard super;
};

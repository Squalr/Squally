#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Hex0 : public HexusCard
{
public:
	static Hex0* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	Hex0();
	virtual ~Hex0();

private:
	typedef HexusCard super;
};

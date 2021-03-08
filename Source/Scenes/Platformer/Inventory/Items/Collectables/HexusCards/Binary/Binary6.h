#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class Binary6 : public HexusCard
{
public:
	static Binary6* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getSerializationKey() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	Binary6();
	~Binary6();

private:
	typedef HexusCard super;
};

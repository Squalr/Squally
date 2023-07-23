#pragma once

#include "Scenes/Platformer/Inventory/Items/Collectables/HexusCards/HexusCard.h"

class LocalizedString;

class SpecialReturnToHand : public HexusCard
{
public:
	static SpecialReturnToHand* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;
	std::string getCardKey() override;

	static const std::string SaveKey;

protected:
	SpecialReturnToHand();
	virtual ~SpecialReturnToHand();

private:
	typedef HexusCard super;
};

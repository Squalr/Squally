#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class EmeraldBand : public Ring
{
public:
	static EmeraldBand* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	EmeraldBand();
	virtual ~EmeraldBand();

private:
	typedef Ring super;
};

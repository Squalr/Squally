#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class EmeraldBand : public Ring
{
public:
	static EmeraldBand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	EmeraldBand();
	virtual ~EmeraldBand();

private:
	typedef Ring super;
};

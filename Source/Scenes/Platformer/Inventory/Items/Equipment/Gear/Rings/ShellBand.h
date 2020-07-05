#pragma once

#include "Scenes/Platformer/Inventory/Items/Equipment/Gear/Rings/Ring.h"

class ShellBand : public Ring
{
public:
	static ShellBand* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	ShellBand();
	virtual ~ShellBand();

private:
	typedef Ring super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Misc.h"

class RamWheel : public Misc
{
public:
	static RamWheel* create();

	Item* clone() override;
	std::string getItemName() override;
	LocalizedString* getString() override;
	std::string getIconResource() override;
	std::string getSerializationKey() override;

	static const std::string SaveKey;

protected:
	RamWheel();
	virtual ~RamWheel();

private:
	typedef Misc super;
};

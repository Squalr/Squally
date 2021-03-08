#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class RamWheel : public Key
{
public:
	static RamWheel* create();

	Item* clone() override;
	const std::string& getItemName() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	RamWheel();
	virtual ~RamWheel();

private:
	typedef Key super;
};

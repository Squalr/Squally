#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class HellKey : public Key
{
public:
	static HellKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	HellKey();
	virtual ~HellKey();

private:
	typedef Key super;
};

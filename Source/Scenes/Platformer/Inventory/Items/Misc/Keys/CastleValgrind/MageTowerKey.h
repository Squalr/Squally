#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MageTowerKey : public Key
{
public:
	static MageTowerKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	MageTowerKey();
	virtual ~MageTowerKey();

private:
	typedef Key super;
};

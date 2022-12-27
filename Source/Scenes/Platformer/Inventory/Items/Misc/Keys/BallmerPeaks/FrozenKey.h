#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class FrozenKey : public Key
{
public:
	static FrozenKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	FrozenKey();
	virtual ~FrozenKey();

private:
	typedef Key super;
};

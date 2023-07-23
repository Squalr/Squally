#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class UnstableConcoction : public Key
{
public:
	static UnstableConcoction* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	UnstableConcoction();
	virtual ~UnstableConcoction();

private:
	typedef Key super;
};

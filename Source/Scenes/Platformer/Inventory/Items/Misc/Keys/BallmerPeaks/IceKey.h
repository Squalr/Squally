#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class IceKey : public Key
{
public:
	static IceKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	IceKey();
	virtual ~IceKey();

private:
	typedef Key super;
};

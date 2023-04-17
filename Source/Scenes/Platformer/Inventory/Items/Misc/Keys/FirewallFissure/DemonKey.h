#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class DemonKey : public Key
{
public:
	static DemonKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	DemonKey();
	virtual ~DemonKey();

private:
	typedef Key super;
};

#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class DemonHeart : public Key
{
public:
	static DemonHeart* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	DemonHeart();
	virtual ~DemonHeart();

private:
	typedef Key super;
};

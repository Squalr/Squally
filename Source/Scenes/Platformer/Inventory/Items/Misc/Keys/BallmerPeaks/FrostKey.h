#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class FrostKey : public Key
{
public:
	static FrostKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	FrostKey();
	virtual ~FrostKey();

private:
	typedef Key super;
};

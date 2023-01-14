#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class AncientKey : public Key
{
public:
	static AncientKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	AncientKey();
	virtual ~AncientKey();

private:
	typedef Key super;
};

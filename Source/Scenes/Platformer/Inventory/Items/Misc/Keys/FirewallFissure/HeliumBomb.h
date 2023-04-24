#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class HeliumBomb : public Key
{
public:
	static HeliumBomb* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	HeliumBomb();
	virtual ~HeliumBomb();

private:
	typedef Key super;
};

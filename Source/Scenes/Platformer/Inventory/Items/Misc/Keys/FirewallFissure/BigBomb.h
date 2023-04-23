#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class BigBomb : public Key
{
public:
	static BigBomb* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	BigBomb();
	virtual ~BigBomb();

private:
	typedef Key super;
};

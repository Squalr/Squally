#pragma once

#include "Scenes/Platformer/Inventory/Items/Misc/Keys/Key.h"

class MinesKey : public Key
{
public:
	static MinesKey* create();

	Item* clone() override;
	LocalizedString* getString() override;
	const std::string& getIconResource() override;
	const std::string& getIdentifier() override;

	static const std::string SaveKey;

protected:
	MinesKey();
	virtual ~MinesKey();

private:
	typedef Key super;
};
